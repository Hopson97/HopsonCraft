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

    constexpr static float NEAR_PLANE  = 0.01;
    constexpr static float FAR_PLANE   = 1000;

    constexpr static float SKY_RED     = 0.12;
    constexpr static float SKY_GREEN   = 0.56;
    constexpr static float SKY_BLUE    = 1;
};

#endif // PLAY_SETTINGS_H
