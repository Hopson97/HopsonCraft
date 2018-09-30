#include <iostream>
#include <fstream>
#include <ctime>

#include "Util/Random.h"
#include "Util/Native.h"

#include "Application.h"
#include "Display.h"

#include "World/Block/BlockData.h"
#include "World/Block/BlockDatabase.h"



#ifdef __WIN32
    extern "C"
    {
        //Enable dedicated graphics
        __declspec(dllexport) bool NvOptimusEnablement = true;
        __declspec(dllexport) bool AmdPowerXpressRequestHighPerformance = true;
    }
#else
    //Include for the linux/apple error message
    #include <unistd.h>
#endif // __WIN32


namespace
{
    void errorMessage(const std::string& message)
    {
        #ifdef __WIN32
            MessageBox(nullptr, message.c_str(), "Error", MB_OK);
            std::cerr << message << std::endl;
        #elif __linux__ || __APPLE__
            execl("/usr/bin/zenity", "zenity", "--error", "--text", message.c_str(), nullptr);
        #else
            std::cerr << message << std::endl;
            std::cin.ignore();
        #endif
    }

    void initilize()
    {
        Display::get(); //Init the display. This must be done in order to enable OpenGL.
        Random::init();

        //This is so that the RNG is more random
        //Or else, first value seems to be the same
        for (int i = 0; i < 15; i++)
        {
            Random::intInRange(0, RAND_MAX);
        }
    }
}



//entry
int main()
{
    try
    {
        initilize();

        Application app;
        app.runMainGameLoop();
        return EXIT_SUCCESS;
    }
    catch(std::exception& e)
    {
        errorMessage(e.what());
        return EXIT_FAILURE;
    }
}

