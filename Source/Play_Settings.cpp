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
    uint32_t renderDistance = (uint32_t)Render_Distance::Normal;
    uint32_t fov            = (uint32_t)Field_Of_Vision::Big;

    uint32_t getRenderDistance()
    {
        //std::cout << renderDistance << std::endl;
        return renderDistance;
    }

    float getFOV()
    {
        return (float)fov;
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
