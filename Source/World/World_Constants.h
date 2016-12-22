#ifndef WORLD_CONSTANTS_H_INCLUDED
#define WORLD_CONSTANTS_H_INCLUDED

namespace World
{
    constexpr static uint16_t   CHUNK_SIZE      = 20,    //Width/ depth of a chunk, height is infinite
                                WATER_LEVEL     = 90,
                                BEACH_LEVEL     = WATER_LEVEL + 4,
                                SNOW_LEVEL      = 260;

}

#endif // WORLD_CONSTANTS_H_INCLUDED
