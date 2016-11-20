#include "noise_generator.h"

#include <cmath>
#include <iostream>
#include <mutex>

#include "../World/Chunk/Chunk.h"

namespace Noise
{
    uint32_t seed;

    uint32_t getSeed()
    {
        return seed;
    }

    void setSeed(uint32_t newSeed)
    {
        seed = newSeed;
    }

    double Generator::findNoise1(int n) const
    {
        n += m_seed;
        n = (n << 13) ^ n;
        auto nn = (n * (n * n * 60493 + 19990303) + 1376312589) & 0x7fffffff; //wot
        return 1.0 - ((double)nn / 1073741824.0); //wot (part 2)
    }

    double Generator::findNoise2(double x, double z) const
    {
        auto n = (int)x + (int)z * 57;
        return findNoise1(n);
    }

    double Generator::interpolate(double a, double b, double z) const
    {
        auto ft = z * 3.1415927;
        auto f = (1.0 - cos(ft)) * 0.5;

        return a * (1.0 - f) + b * f;
    }

    double Generator::noise(double x, double z) const
    {
        auto floorX = (double)((int)x); //This is kinda a cheap way to floor a double integer.
        auto floorZ = (double)((int)z);

        auto    s = 0.0,
                t = 0.0,
                u = 0.0,
                v = 0.0;//Integer declaration

        s = findNoise2(floorX,      floorZ);
        t = findNoise2(floorX + 1,  floorZ);
        u = findNoise2(floorX,      floorZ + 1);//Get the surrounding values to calculate the transition.
        v = findNoise2(floorX + 1,  floorZ + 1);

        auto rec1 = interpolate(s, t, x - floorX);//Interpolate between the values.
        auto rec2 = interpolate(u, v, x - floorX);//Here we use x-floorX, to get 1st dimension. Don't mind the x-floorX thingie, it's part of the cosine formula.
        auto rec3 = interpolate(rec1, rec2, z - floorZ);//Here we use y-floorZ, to get the 2nd dimension.
        return rec3;
    }

    // Here we get how terrain at X, Y is high. zoomget is only for some testing reasons.
    // Here you can edit maximum and minimum level of height.
    int Generator::getValue(int x, int z, int tileX, int tileZ) const
    {
        auto newX = (x + (tileX * Chunk::SIZE));
        auto newZ = (z + (tileZ * Chunk::SIZE));

        if (newX < 0 || newZ < 0) return Chunk::WATER_LEVEL - 1;

        auto totalValue   = 0.0;

        //Shorthand
        Data nf = m_noiseFunction;

        for (auto a = 0; a < nf.octaves - 1; a++)      //This loops trough the octaves.
        {
            auto frequency = pow(2.0, a) / 2.0f;     //This increases the frequency with every loop of the octave.
            auto amplitude = pow(nf.roughness, a);       //This decreases the amplitude with every loop of the octave.
            totalValue += noise(((double)newX) * frequency / nf.smoother,
                                ((double)newZ) / nf.smoother * frequency)
                                * amplitude;
        }

        int height = (int)((((totalValue + 1) / 2.0) * (nf.amplitudeMultiplier * 1.2)) + nf.heightOffset) / 1.005;

        if (height < 0 ) height = 0;
        return height;
    }

    void Generator::setNoiseFunction(const Noise::Data& data)
    {
        m_noiseFunction = data;
    }

    uint32_t Generator::getSeed()
    {
        return m_seed;
    }

    void Generator::setSeed(uint32_t newSeed)
    {
        m_seed = newSeed;
    }

}
