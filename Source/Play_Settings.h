#ifndef PLAY_SETTINGS_H
#define PLAY_SETTINGS_H

#include <cstdint>

namespace Settings
{
    enum class Render_Distance
    {
        Blind       = 6,
        Near        = 12,
        Normal      = 18,
        Far         = 24,   //Far, Very Far and Extream are not very good as they blocked by fog
        Very_Far    = 28,
        Extreame    = 34
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

    void setRenderDistance  (Render_Distance distance);
    void setFOV             (Field_Of_Vision fov);

    extern const float NEAR_PLANE;
    extern const float FAR_PLANE;

    extern const float SKY_RED;
    extern const float SKY_GREEN;
    extern const float SKY_BLUE;
};

#endif // PLAY_SETTINGS_H
