#ifndef WORLD_SETTINGS_H_INCLUDED
#define WORLD_SETTINGS_H_INCLUDED

#include <cstdint>
#include <string>

#include "../Temp/Noise_Generator.h"

struct World_Settings
{
    std::string name;
    std::string generator;
    int32_t     renderDistance;
    float       seed;
    bool        isSuperFlat        = false;
};

#endif // WORLD_SETTINGS_H_INCLUDED
