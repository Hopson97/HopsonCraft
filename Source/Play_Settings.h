#ifndef PLAY_SETTINGS_H
#define PLAY_SETTINGS_H

#include <cstdint>

class Settings
{
    public:
        Settings();

        uint32_t getRenderDistance();

        const static float FOV;
        const static float NEAR_PLANE;
        const static float FAR_PLANE;

        const static float SKY_RED;
        const static float SKY_GREEN;
        const static float SKY_BLUE;

    private:
        uint32_t m_renderDistance = 20;
};

#endif // PLAY_SETTINGS_H
