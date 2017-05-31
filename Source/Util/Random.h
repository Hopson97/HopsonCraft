#ifndef RANDOM_H_INCLUDED
#define RANDOM_H_INCLUDED

#include <cstdint>
#include <random>
#include <ctime>

namespace Random
{
    void init();
    int64_t intInRange (int64_t lowBound, int64_t highBound);

    template<typename RandomEngine = std::mt19937>
    class Generator
    {
        public:
            Generator(uint64_t seed = std::time(nullptr))
            {
                m_device.seed(seed);
            }

            void setSeed(uint64_t seed)
            {
                m_device.seed(seed);
            }

            int64_t intInRange (int64_t lowBound, int64_t highBound)
            {
                std::uniform_int_distribution<int32_t> dist(lowBound, highBound);
                return dist (m_device);
            }

        private:
            RandomEngine m_device;
    };
}

#endif // RANDOM_H_INCLUDED
