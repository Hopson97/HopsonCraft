#include <cstdlib>
#include <iostream>
#include <string>

#include "Application.h"

#include "Util/Random.h"
#include "Util/Debug_Display.h"
#include "Util/Display.h"
#include "Util/Noise_Generator.h"

#include "World/Gen/World_Generator.h"
#include "World/Block/D_Blocks.h"


int main()
{
    Random::setSeed(time(nullptr));
    Noise::setSeed(Random::integer(0, 32000) * Random::integer(0, 32000));
    Block::initBlockDatabase();

    Display::create("MattCraft");
    Debug_Display::init();

    Application app;
    app.runMainLoop();

    return EXIT_SUCCESS;
}











