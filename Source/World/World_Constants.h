#ifndef WORLD_CONSTANTS_H_INCLUDED
#define WORLD_CONSTANTS_H_INCLUDED

#include <cstdint>

constexpr int32_t   CHUNK_SIZE      = 16,
                    CHUNK_VOLUME    = CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE,
                    CHUNK_AREA      = CHUNK_SIZE * CHUNK_SIZE;

constexpr int8_t    MAX_LIGHT = 10;


#endif // WORLD_CONSTANTS_H_INCLUDED
