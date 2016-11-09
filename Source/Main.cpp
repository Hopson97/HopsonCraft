#include <cstdlib>
#include <iostream>
#include <string>

#include "Application.h"

#include "Debug_Display.h"
#include "Display.h"
#include "Noise_Generator.h"
#include "Block/D_Blocks.h"
#include "Random.h"

int main()
{
    Random::setSeed(time(nullptr));
    //Noise_Generator::setSeed(Random::integer(0, 32000) * Random::integer(0, 32000));
    Noise_Generator::setSeed(5);

    Block::initBlockDatabase();

    Display::create("MattCraft");
    Debug_Display::init();

    Application app;
    app.runMainLoop();

    return EXIT_SUCCESS;
}











