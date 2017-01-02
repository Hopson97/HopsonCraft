#ifndef WORLD_CONSTANTS_H_INCLUDED
#define WORLD_CONSTANTS_H_INCLUDED

#include <cmath>

namespace World_Constants
{
    constexpr static uint16_t   CHUNK_SIZE      = 20,
                                CHUNK_HEIGHT    = 300,
                                WATER_LEVEL     = 90,
                                BEACH_LEVEL     = WATER_LEVEL + 4,
                                SNOW_LEVEL      = 243,
                                CHUNK_AREA      = World_Constants::CHUNK_SIZE * World_Constants::CHUNK_SIZE,
                                MAX_LIGHT_VALUE = 12;
}

#endif // WORLD_CONSTANTS_H_INCLUDED
