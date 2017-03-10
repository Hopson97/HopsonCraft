#ifndef RANDOM_H_INCLUDED
#define RANDOM_H_INCLUDED

#include <cstdint>

namespace Random
{
    void init();
    int32_t     intInRange(int32_t lowBound, int32_t highBound);
    uint64_t    uint64InRange(uint64_t lowBound, uint64_t highBound);
}

#endif // RANDOM_H_INCLUDED
