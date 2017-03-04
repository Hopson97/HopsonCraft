#include <iostream>
#include <thread>

#include "Display.h"
#include "Application.h"
#include "Util/Random.h"

int main() try
{
    Random      ::init();
    Display     ::init();

    Application app;
    app.runMainGameLoop();

    return 0;
}
catch(std::exception& e)
{
    std::cout << e.what() << std::endl;
    std::cin.ignore();
}


