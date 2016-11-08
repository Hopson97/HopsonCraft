#ifndef NOISE_GENERATOR_H
#define NOISE_GENERATOR_H

namespace Noise_Generator
{
    struct Data
    {
        Data() = default;
        Data(int octaves, int ampMult, double rough, double smooth)
        :   octaves             (octaves)
        ,   amplitudeMultiplier (ampMult)
        ,   roughness           (rough)
        ,   smoother            (smooth) {}
        int octaves = 8;
        int amplitudeMultiplier = 240;
        double roughness = 0.48;
        double smoother = 190;
    };

    int getHeight(int x, int z, int tileX, int tileZ);

    void setNoiseFunction (const Data& d);

    int getSeed     ();
    void setSeed    (int newSeed);
}
#endif // NOISE_GENERATOR_H
