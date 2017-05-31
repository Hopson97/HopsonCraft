#ifndef WORLD_SETTINGS_H_INCLUDED
#define WORLD_SETTINGS_H_INCLUDED

#include <cstdint>
#include <string>

#include "Generators/Noise.h"

struct World_Settings
{
    std::string name = "Test World";
    float       seed;
};

#endif // WORLD_SETTINGS_H_INCLUDED
