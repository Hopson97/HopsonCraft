#ifndef WORLD_CONSTANTS_H_INCLUDED
#define WORLD_CONSTANTS_H_INCLUDED

#include <cmath>

namespace World_Constants
{
    constexpr static uint16_t   CHUNK_SIZE      = 20,    //Width/ depth of a chunk, height is infinite
                                WATER_LEVEL     = 90,
                                BEACH_LEVEL     = WATER_LEVEL + 4,
                                SNOW_LEVEL      = 250,
                                CHUNK_AREA      = World_Constants::CHUNK_SIZE * World_Constants::CHUNK_SIZE;
}

#endif // WORLD_CONSTANTS_H_INCLUDED
