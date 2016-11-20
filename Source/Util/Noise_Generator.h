#ifndef NOISE_GENERATOR_H
#define NOISE_GENERATOR_H

namespace Noise
{
    struct Data
    {
        Data() = default;
        Data(int octaves, int ampMult, double rough, double smooth, int heightOffset)
        :   octaves             (octaves)
        ,   amplitudeMultiplier (ampMult)
        ,   roughness           (rough)
        ,   smoother            (smooth)
        ,   heightOffset        (heightOffset) {}
        int octaves = 8;
        int amplitudeMultiplier = 240;
        double roughness = 0.48;
        double smoother = 190;
        int heightOffset = 0;
    };

    long long getSeed     ();
    void setSeed    (long long newSeed);

    class Generator
    {
        public:
            int getValue(int x, int z, int tileX, int tileZ) const;

            void setNoiseFunction(const Noise::Data& data);

            long long getSeed     ();
            void setSeed    (long long newSeed);

        private:
            double findNoise1(int n) const;
            double findNoise2(double x, double z) const;
            double interpolate(double a, double b, double z) const;
            double noise(double x, double z) const;


            Noise::Data m_noiseFunction;
            long long m_seed;

    };
}
#endif // NOISE_GENERATOR_H
