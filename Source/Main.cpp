#include <iostream>
#include <fstream>

#include "Display.h"
#include "Application.h"
#include "Util/Random.h"
#include "Util/Config.h"
#include "Util/ConfigParser.h"
#include "Util/Singleton.h"

#include "World/Block/Block_Database.h"

#include "Temp/Noise_Generator.h"

namespace
{
    void initilize()
    {
        Random  ::init();
        Display ::init();

        Block::Database::get();
    }

    void loadConfig()
    {
        const std::string fileName = "HopsonCraft.conf";
        std::ifstream inFile (fileName);

        if(inFile.is_open())
        {
            Singleton<Config>::get().loadFromStream(fileName, inFile);
        }
    }
}

int main() try
{
/*
    Noise::Generator m_noiseGen;
    m_noiseGen.setSeed(555);
    m_noiseGen.setNoiseFunction({8, 100, 0.45, 180, 0});

    uint64_t total = 0;
    std::vector<double> test;
    for (int i = 0 ; i < 100000 ; i++)
    {
        int h = m_noiseGen.getValue(i, i * i, i * 2, i * i * i);
        test.push_back(h);
        total += h;
    }

    std::cout << "MIN: " << *std::min_element(test.begin(), test.end()) << "\n";
    std::cout << "MAX: " << *std::max_element(test.begin(), test.end()) << "\n";
    std::cout << "AVG: " << total / 100000 << std::endl;
    */

    initilize();
    loadConfig();

    Application app;
    app.runMainGameLoop();

    return 0;
}
catch(std::exception& e)
{
    std::cout << e.what() << std::endl;
    std::cin.ignore();
}


