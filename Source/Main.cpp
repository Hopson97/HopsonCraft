#include <cstdlib>
#include <iostream>
#include <string>

#ifdef __WIN32
    #define _WIN32_WINNT 0x0500 //For getting console window
    #include "windows.h"
#endif // __WIN32

#include "Application.h"
#include "Window.h"
#include "Height_Generator.h"
#include "Random.h"

namespace
{
    void getWorldData ();
    void setConsoleLocation();
}

int main()
{
    srand ( time ( nullptr ) );
    getWorldData();
    setConsoleLocation();

    Window::create( "MattCraft (" + std::to_string ( Window::WIDTH ) + " x " + std::to_string ( Window::HEIGHT) + ")" );
    Application app;
    app.runLoop();

    return EXIT_SUCCESS;
}


namespace
{
    void randomWorldData()
    {
        std::cout << "Generating random data. \n";
        double amplitude    = Random::integer( 170, 250 );
        double roughness    = Random::decimalD( 0.25, 0.8, 3);
        double octaves      = Random::integer( 3, 6);
        int seed            = Random::integer(0, 32000) * Random::integer(0, 32000);
        int worldSize       = Random::integer(15, 18);

        World::worldSize = worldSize;
        std::cout << "World size: " << worldSize << std::endl;

        Height_Generator::setUp( amplitude, roughness, octaves, seed );
    }

    void customWorldData()
    {
        double amplitude  = 0;
        double roughness  = 0;
        double octaves    = 0;
        int seed          = 0;
        int size          = 0;

        std::cout << "Please enter amplitude: (Recommended: 170 to 250) \n";
        std::cin >> amplitude;

        std::cout << "Please enter roughness: (Recommended: 0.3 to 0.7) \n";
        std::cin >> roughness;

        std::cout << "Please enter octaves (effects smoothness): (Recommended: 3 to 6) \n";
        std::cin >> octaves;

        std::cout << "Please enter the seed: (Enter -1 for a random seed) \n";
        std::cin >> seed;

        std::cout << "Please enter world size (Area, in chunks) (Recommended: 16 to 32) \n";
        std::cin >> size;

        World::worldSize = size;


        Height_Generator::setUp( amplitude, roughness, octaves, seed );
    }

    void getWorldData ()
    {
        std::cout << "Welcome to MattCraft! \n";

        std::cout   << "Would you like to enter custom generation data? \n"
                    << "1. Yes. \n"
                    << "2. No.  \n";

        int option = 0;
        std::cin >> option;

        if  ( option == 1 )
        {
            customWorldData();
        }
        else
        {
            randomWorldData();
        }

    }

    void setConsoleLocation()
    {
        #ifdef __WIN32
            int consoleWidth = 500;
            HWND console = GetConsoleWindow();
            MoveWindow(console, Window::WIDTH - 250, 0, consoleWidth, Window::HEIGHT, TRUE);
        #endif // __WIN32
    }
}










