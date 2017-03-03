#include "Display.h"

#include "Application.h"

#include <iostream>

int main() try
{
    Display::init();

    Application app;

    app.runMainGameLoop();

    return 0;
}
catch(std::exception& e)
{
    std::cout << e.what() << std::endl;
    std::cin.ignore();
}
