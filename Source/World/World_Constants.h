#ifndef WORLD_CONSTANTS_H_INCLUDED
#define WORLD_CONSTANTS_H_INCLUDED

#include <cstdint>

namespace
{
    constexpr int32_t   CHUNK_SIZE      = 16,
                        CHUNK_SIZE_P    = CHUNK_SIZE + 1, //Chunk size plus one
                        CHUNK_VOLUME    = CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE,
                        CHUNK_AREA      = CHUNK_SIZE * CHUNK_SIZE,
                        CHUNK_AREA_P    = CHUNK_SIZE_P * CHUNK_SIZE_P,
                        WATER_LEVEL     = 70,
                        BEACH_LEVEL     = WATER_LEVEL + 2;

    constexpr int8_t    MAX_LIGHT       = 10;

    constexpr float     BLOCK_SIZE      = 1.0f;
}


#endif // WORLD_CONSTANTS_H_INCLUDED
