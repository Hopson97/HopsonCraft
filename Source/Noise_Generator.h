#ifndef NOISE_GENERATOR_H
#define NOISE_GENERATOR_H

namespace Noise_Generator
{
    int getHeight(int x, int z, int tileX, int tileZ);

    int getSeed     ();
    void setSeed    (int newSeed);
}
#endif // NOISE_GENERATOR_H
