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

    void runGame()
    {
        initilize();
        loadConfig();

        Application app;
        app.runMainGameLoop();
    }

    void noiseTest(int trials)
    {
        Noise::Generator m_noiseGen;
        m_noiseGen.setSeed(555);
        m_noiseGen.setNoiseFunction({8, 100, 0.53, 240, 0});

        uint64_t total = 0;
        std::vector<double> test;
        for (int i = 0 ; i < trials ; i++)
        {
            int h = m_noiseGen.getValue(i, i, i, i);
            test.push_back(h);
            total += h;
        }

        std::cout << "MIN: " << *std::min_element(test.begin(), test.end()) << "\n";
        std::cout << "MAX: " << *std::max_element(test.begin(), test.end()) << "\n";
        std::cout << "AVG: " << total / trials << std::endl;
    }
}

int main() try
{
    runGame();
    //noiseTest(1000000);
    return 0;
}
catch(std::exception& e)
{
    std::cout << e.what() << std::endl;
    std::cin.ignore();
}


