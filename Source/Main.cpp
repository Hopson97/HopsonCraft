#include <iostream>
#include <fstream>
#include <ctime>

#include "Util/Random.h"

#include "Util/Config.h"
#include "Util/Singleton.h"

#include "Temp/Noise_Generator.h"

#include "Application.h"
#include "Display.h"

#ifdef __WIN32
    #include <windows.h>

    //Enable dedicated graphics
    extern "C"
    {
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
        #else // __WIN32
            std::cerr << message << std::endl;
        #endif
/** @TODO Put correct headers for these bad boys
        #elif __linux
            const std::string command = "zenity --error --text \"" + message + "\"";
            system(command.c_str());
        #elif __APPLE__
            const std::string command = "osascript -e 'tell app \"System Events\" to display dialog \"" + message + "\" buttons {\"OK\"} default button 1 with icon caution with title \"Error\"'";
            system(command.c_str());
        #else
            std::cerr << message << std::endl;
            std::cin.ignore();
        #endif
*/
    }

    void initilize()
    {
        Random  ::init();
        Display ::init();

        for (int i = 0; i < 30; i++)
        {
            Random::intInRange(0, 63464); //This is so that the RNG is more random
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


