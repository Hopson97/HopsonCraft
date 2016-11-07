#include "noise_generator.h"

#include <cmath>

#include "Chunk.h"

namespace Noise_Generator
{
    int seed;

    double FindNoise1(int n)
    {
        n += seed;
        n = (n << 13) ^ n;
        auto nn = (n * (n * n * 60493 + 19990303) + 1376312589) & 0x7fffffff; //wot
        return 1.0 - ((double)nn / 1073741824.0); //wot (part 2)
    }

    double FindNoise2(double x, double y)
    {
        auto n = (int)x + (int)y * 57;
        return FindNoise1(n);
    }

    double interpolate(double a, double b, double x)
    {
        auto ft = x * 3.1415927;
        auto f = (1.0 - cos(ft)) * 0.5;
        return a * (1.0 - f) + b * f;
    }

    double noise(double x, double y, int seed)
    {
        auto floorX = (double)((int)x); //This is kinda a cheap way to floor a double integer.
        auto floorY = (double)((int)y);

        auto    s = 0.0,
                t = 0.0,
                u = 0.0,
                v = 0.0;//Integer declaration

        s = FindNoise2(floorX,      floorY);
        t = FindNoise2(floorX + 1,  floorY);
        u = FindNoise2(floorX,      floorY + 1);//Get the surrounding values to calculate the transition.
        v = FindNoise2(floorX + 1,  floorY + 1);

        auto rec1 = interpolate(s, t, x - floorX);//Interpolate between the values.
        auto rec2 = interpolate(u, v, x - floorX);//Here we use x-floorX, to get 1st dimension. Don't mind the x-floorX thingie, it's part of the cosine formula.
        auto rec3 = interpolate(rec1, rec2, y - floorY);//Here we use y-floorY, to get the 2nd dimension.
        return rec3;
    }

    // Here we get how terrain at X, Y is high. zoomget is only for some testing reasons.
    // Here you can edit maximum and minimum level of height.
    int getHeight(int x, int y, int tileX, int tileZ)
    {
        x += tileX * Chunk::SIZE;
        y += tileZ * Chunk::SIZE;

        auto p = 0.42;
        auto zoom = 150.0;
        auto getnoise = 0.0;
        auto octaves = 7;
        for (auto a = 0; a < octaves - 1; a++)//This loops trough the octaves.
        {
            auto frequency = pow(2.0, a) / 1.3;//This increases the frequency with every loop of the octave.
            auto amplitude = pow(p, a) / 1.3;//This decreases the amplitude with every loop of the octave.
            getnoise += noise(((double)x) * frequency / zoom, ((double)y) / zoom * frequency,seed) * amplitude;//This uses our perlin noise functions. It calculates all our zoom and frequency and amplitude
        }

        int height = (int)(((getnoise + 1) / 2.0) * (250));

        if (height < 0) height = 0;
        return height;
    }

    int getSeed()
    {
        return seed;
    }

    void setSeed(int newSeed)
    {
        seed = newSeed;
    }
}
