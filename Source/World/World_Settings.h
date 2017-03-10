#ifndef WORLD_SETTINGS_H_INCLUDED
#define WORLD_SETTINGS_H_INCLUDED

#include <cstdint>

struct World_Settings
{
    World_Settings(uint32_t waterLevel, uint32_t beachLevel)

    const uint32_t  WATER_LEVEL,
                    BEACH_LEVEL;
};

#endif // WORLD_SETTINGS_H_INCLUDED
