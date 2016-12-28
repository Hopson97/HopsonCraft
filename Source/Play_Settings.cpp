#include "Play_Settings.h"

#include <fstream>
#include <iostream>


namespace Settings
{
    uint32_t renderDistance = (uint32_t)Render_Distance::Normal;
    uint32_t fov            = (uint32_t)Field_Of_Vision::Big;

    uint32_t getRenderDistance()
    {
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
