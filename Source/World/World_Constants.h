#ifndef WORLD_CONSTANTS_H_INCLUDED
#define WORLD_CONSTANTS_H_INCLUDED

#include <cstdint>

namespace
{
    constexpr static int32_t    CHUNK_SIZE      = 16,
                                CHUNK_VOLUME    = CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE,
                                CHUNK_AREA      = CHUNK_SIZE * CHUNK_SIZE,
                                WATER_LEVEL     = 73;

    constexpr static int8_t     MAX_LIGHT       = 10;

    constexpr static float      BLOCK_SIZE      = 1.0f;
}


#endif // WORLD_CONSTANTS_H_INCLUDED
