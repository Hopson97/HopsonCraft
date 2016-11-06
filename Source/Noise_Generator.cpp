#include "noise_generator.h"

#include <cmath>

#include "Chunk.h"

namespace Noise_Generator
{
    int seed;

// Terrain generation.
// Perlin noise and other things I don't get.

    double FindNoise1(int n,int seed)
    {
                    n += seed;
        n = (n << 13) ^ n;
        int nn = (n * (n * n * 60493 + 19990303) + 1376312589) & 0x7fffffff;
        return 1.0 - ((double)nn / 1073741824.0);
    }

    double FindNoise2(double x, double y,int seed)
    {
        int n = (int)x + (int)y * 57;
        return FindNoise1(n,seed);
    }

    double interpolate(double a, double b, double x)
    {
        double ft = x * 3.1415927;
        double f = (1.0 - cos(ft)) * 0.5;
        return a * (1.0 - f) + b * f;
    }

    double noise(double x, double y,int seed)
    {
        double floorx = (double)((int)x);//This is kinda a cheap way to floor a double integer.
        double floory = (double)((int)y);
        double s, t, u, v;//Integer declaration
        s = FindNoise2(floorx, floory,seed);
        t = FindNoise2(floorx + 1, floory,seed);
        u = FindNoise2(floorx, floory + 1,seed);//Get the surrounding pixels to calculate the transition.
        v = FindNoise2(floorx + 1, floory + 1,seed);
        double int1 = interpolate(s, t, x - floorx);//Interpolate between the values.
        double int2 = interpolate(u, v, x - floorx);//Here we use x-floorx, to get 1st dimension. Don't mind the x-floorx thingie, it's part of the cosine formula.
        return interpolate(int1, int2, y - floory);//Here we use y-floory, to get the 2nd dimension.
    }

    // Here we get how terrain at X, Y is high. zoomget is only for some testing reasons.
    // Here you can edit maximum and minimum level of height.
    // Also here you pass seed. It's int.

    int getHeight(int x, int y, int tileX, int tileZ)
    {
        x += tileX * Chunk::SIZE;
        y += tileZ * Chunk::SIZE;


        double p = 0.5;
        double zoom = 150;
        double getnoise = 0;
        int octaves = 4;
        for (int a = 0; a < octaves - 1; a++)//This loops trough the octaves.
        {
            double frequency = pow(2.0, a);//This increases the frequency with every loop of the octave.
            double amplitude = pow(p, a);//This decreases the amplitude with every loop of the octave.
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
