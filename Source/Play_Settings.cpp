#include "Play_Settings.h"

#include <fstream>
#include <iostream>

constexpr float Settings::FOV = 95;
constexpr float Settings::NEAR_PLANE  = 0.01;
constexpr float Settings::FAR_PLANE   = 1000;

constexpr float Settings::SKY_RED     = 0.12;
constexpr float Settings::SKY_GREEN   = 0.56;
constexpr float Settings::SKY_BLUE    = 1;

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

uint32_t Settings::getRenderDistance()
{
    return m_renderDistance;
}
