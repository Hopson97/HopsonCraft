#include <iostream>
#include <fstream>

#include "Display.h"
#include "Application.h"
#include "Util/Random.h"
#include "Util/Config.h"
#include "Util/ConfigParser.h"
#include "Util/Singleton.h"
#include "World/Chunk/CSection.h"

#include "World/Block/Block_Database.h"

#include "Temp/Noise_Generator.h"

#ifdef __WIN32
#include <windows.h>
#endif // __WIN32

namespace
{
    void errorMessage(const std::string& message)
    {
        #ifdef __WIN32
            MessageBox(nullptr, message.c_str(), "Error", MB_OK);
        #else // __WIN32
            std::cerr << message << std::endl;
        #endif
    }

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

        float total = 0;
        std::vector<double> test;
        for (int i = 0 ; i < trials ; i++)
        {
            float h = m_noiseGen.getValue(i, i, i, i);
            test.push_back(h);
            total += h;
        }

        std::cout << "MIN: " << *std::min_element(test.begin(), test.end()) << "\n";
        std::cout << "MAX: " << *std::max_element(test.begin(), test.end()) << "\n";
        std::cout << "AVG: " << total / trials << std::endl;
    }
}

//====================== i put this here because
//MAIN IS HERE
int main() try
{
    runGame();
    return 0;
}
catch(std::out_of_range& e)
{
    std::string msg = e.what();
    errorMessage(msg);
    std::cin.ignore();
}
catch(std::runtime_error& e)
{
    std::string msg = e.what();
    errorMessage(msg);
    std::cin.ignore();
}
catch(...)
{
    errorMessage("Unknown error.");
    std::cin.ignore();
}


