#include "Play_Settings.h"

#include <fstream>
#include <iostream>

const float Settings::NEAR_PLANE  = 0.01;
const float Settings::FAR_PLANE   = 1000;

const float Settings::SKY_RED     = 0.12;
const float Settings::SKY_GREEN   = 0.56;
const float Settings::SKY_BLUE    = 1;

namespace Settings
{
    auto sRenderDistance = Render_Distance::Normal;
    auto sFov            = Field_Of_Vision::Big;

    uint32_t getRenderDistance()
    {
        //std::cout << renderDistance << std::endl;
        return (uint32_t)sRenderDistance;
    }

    float getFOV()
    {
        return (float)sFov;
    }

    void setRenderDistance(Render_Distance distance)
    {
        sRenderDistance = distance;
    }

    void setFOV(Field_Of_Vision fov)
    {
        sFov = fov;
    }

    void load()
    {
        std::ifstream inFile("Data/Settings.txt");

        std::string line;
        while (std::getline(inFile, line))
        {
            if (line == "rd")
            {
                //inFile >> renderDistance;
            }
            else if (line == "fov")
            {
                //inFile >> fov;
            }
        }
    }
}
