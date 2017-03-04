#include <iostream>
#include <thread>

#include "Display.h"
#include "Application.h"
#include "Util/Random.h"
#include "Util/Thread_Pool_Impl.h"

int main() try
{
    std::cout << std::thread::hardware_concurrency() << "\n";

    Random      ::init();
    Display     ::init();
    Thread_Pool ::init();

    Application app;
    app.runMainGameLoop();

    return 0;
}
catch(std::exception& e)
{
    std::cout << e.what() << std::endl;
    std::cin.ignore();
}
