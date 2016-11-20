#include "Play_Settings.h"

#include <fstream>

namespace Settings
{
    int renderDistance = 0;

    void init()
    {
        std::ifstream inFile("Data/Settings.txt");

        std::string line;
        while (std::getline(inFile, line))
        {
            if (line == "rd")
            {
                inFile >> renderDistance;
            }
        }
    }

    int getRenderDistance()
    {
        return renderDistance;
    }
}
