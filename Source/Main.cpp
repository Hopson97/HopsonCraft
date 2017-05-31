#include <iostream>
#include <fstream>
#include <ctime>

#include "Util/Random.h"

#include "Util/Config.h"
#include "Util/Singleton.h"

#include "World/Generators/Noise.h"

#include "Application.h"
#include "Display.h"

#include "Util/Native.h"

#ifdef __WIN32
    extern "C"
    {
        //Enable dedicated graphics
        __declspec(dllexport) bool NvOptimusEnablement = true;
        __declspec(dllexport) bool AmdPowerXpressRequestHighPerformance = true;
    }
#endif // __WIN32


namespace
{
    void noiseTest(int trials)
    {
        Random::init();
        Noise::Generator m_noiseGen;
        m_noiseGen.setSeed(Random::intInRange(0, 999999));
        m_noiseGen.setNoiseFunction({5, 500, 0.4, 5000});

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

    void errorMessage(const std::string& message)
    {
        #ifdef __WIN32
            MessageBox(nullptr, message.c_str(), "Error", MB_OK);
            std::cerr << message << std::endl;
        #elif __linux__ || __APPLE__
            const std::string command = "zenity --error --text \"" + message + "\"";
            system(command.c_str());
        #else
            std::cerr << message << std::endl;
            std::cin.ignore();
        #endif
    }

    void initilize()
    {
        Random  ::init();
        Display ::init();

        for (int i = 0; i < 30; i++)
        {
            Random::intInRange(0, 6346554); //This is so that the RNG is more random
        }
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
}

/*
    ~
    ~   The main function is here guise :^)
    ~
*/
int main() try
{
    runGame();
    return 0;
}
catch(std::exception& e)
{
    errorMessage(std::string(e.what()));
}


