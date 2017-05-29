#ifndef NOISE_GENERATOR_H
#define NOISE_GENERATOR_H

#include <cstdint>
#include <iostream>

namespace Noise
{
    struct Data
    {
        Data() = default;
        Data(uint64_t numOctaves,
             uint64_t ampMult,
             double rough,
             double smooth,
             uint64_t heightMod = 0)
        :   octaves             (numOctaves)
        ,   amplitudeMultiplier (ampMult)
        ,   roughness           (rough)
        ,   smoother            (smooth)
        ,   heightMod           (heightMod)
        {}
        uint64_t    octaves             = 8;
        uint64_t    amplitudeMultiplier = 240;
        double      roughness        = 0.48;
        double    smoother         = 190;
        uint64_t    heightMod           = 0;

        void print() const
        {
            std::cout   << "Octaves:    " << octaves
                        << "Amplitude:  " << amplitudeMultiplier
                        << "Roughness:  " << roughness
                        << "Smoother:   " << smoother << "\n";

        }
    };

    class Generator
    {
        public:
            double getValue(int x, int z, int tileX, int tileZ) const;

            void setNoiseFunction(const Noise::Data& data);

            uint64_t getSeed    ();
            void setSeed        (uint64_t newSeed);

        private:
            double findNoise1   (int n)                         const;
            double findNoise2   (double x, double z)            const;
            double lerp         (double a, double b, double z)  const;
            double noise        (double x, double z)            const;

            Noise::Data m_noiseFunction;
            uint64_t m_seed;

    };
}
#endif // NOISE_GENERATOR_H
