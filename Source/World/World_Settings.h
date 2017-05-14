#ifndef WORLD_SETTINGS_H_INCLUDED
#define WORLD_SETTINGS_H_INCLUDED

#include <cstdint>
#include <string>

#include "../Temp/Noise_Generator.h"

struct World_Settings
{
    std::string name;
    Noise::Data noiseData;
    int32_t     worldSize;
    float       seed;
    bool        isSuperFlat        = false;
    bool        isExperimentalMode = false;
};

#endif // WORLD_SETTINGS_H_INCLUDED
