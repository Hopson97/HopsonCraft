#ifndef WorldSettings_H_INCLUDED
#define WorldSettings_H_INCLUDED

#include <cstdint>
#include <string>

#include "Generators/Noise.h"

struct WorldSettings
{
    std::string name = "Test World";
    float       seed;
};

#endif // WorldSettings_H_INCLUDED
