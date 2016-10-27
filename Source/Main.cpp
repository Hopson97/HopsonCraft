#include <cstdlib>
#include <iostream>
#include <string>

#ifdef __WIN32
    #define _WIN32_WINNT 0x0500 //For getting console window
    #include "windows.h"
#endif // __WIN32

#include "Application.h"

#include "Debug_Display.h"
#include "Display.h"
#include "Height_Generator.h"

namespace
{
    void setConsoleLocation();
}


int main()
{
    srand ( time ( nullptr ) );

    setConsoleLocation();

    Display::create( "MattCraft (" + std::to_string ( Display::WIDTH ) + " x " + std::to_string ( Display::HEIGHT) + ")" );
    Debug_Display::init();
    Height_Generator::setUp();

    Application app;
    app.runMainLoop();

    return EXIT_SUCCESS;
}


namespace
{
    void setConsoleLocation()
    {

        #ifdef __WIN32
            int consoleWidth = 500;
            HWND console = GetConsoleWindow();
            MoveWindow(console, -500, 0, consoleWidth, Display::HEIGHT, TRUE);
        #endif // __WIN32
    }
}










