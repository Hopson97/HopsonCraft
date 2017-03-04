#ifndef WORLD_CONSTANTS_H_INCLUDED
#define WORLD_CONSTANTS_H_INCLUDED

#include <cstdint>

namespace World_Constants
{
    constexpr int32_t   CH_SIZE      = 24,
                        CH_VOLUME    = CH_SIZE * CH_SIZE * CH_SIZE,
                        CH_AREA      = CH_SIZE * CH_SIZE;
}

#endif // WORLD_CONSTANTS_H_INCLUDED
