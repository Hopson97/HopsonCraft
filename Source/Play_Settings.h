#ifndef PLAY_SETTINGS_H
#define PLAY_SETTINGS_H

#include <cstdint>

class Settings
{
    public:
        Settings();

        uint8_t getRenderDistance();

        constexpr static float FOV = 100;
        constexpr static float NEAR_PLANE  = 0.01;
        constexpr static float FAR_PLANE   = 1000;

        constexpr static float SKY_RED     = 0.12;
        constexpr static float SKY_GREEN   = 0.56;
        constexpr static float SKY_BLUE    = 1;

    private:
        uint8_t m_renderDistance = 20;
};

#endif // PLAY_SETTINGS_H
