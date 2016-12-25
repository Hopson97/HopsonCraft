#include "Play_Settings.h"

#include <fstream>

Settings::Settings()
{
    std::ifstream inFile("Data/Settings.txt");

    std::string line;
    while (std::getline(inFile, line))
    {
        if (line == "rd")
        {
            inFile >> m_renderDistance;
        }
    }
}

uint8_t Settings::getRenderDistance()
{
    return m_renderDistance;
}
