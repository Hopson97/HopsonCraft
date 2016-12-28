#ifndef PLAY_SETTINGS_H
#define PLAY_SETTINGS_H

#include <cstdint>

namespace Settings
{
    enum class Render_Distance
    {
        Blind       = 6,
        Near        = 10,
        Normal      = 20,
        Far         = 26,
        Extreame    = 32,
    };

    enum class Field_Of_Vision
    {
        Small   = 70,
        Medium  = 90,
        Big     = 110,
        Wide    = 130,
    };

    void load();

    uint32_t    getRenderDistance();
    float       getFOV();

    extern const float NEAR_PLANE;
    extern const float FAR_PLANE;

    extern const float SKY_RED;
    extern const float SKY_GREEN;
    extern const float SKY_BLUE;
};

#endif // PLAY_SETTINGS_H
