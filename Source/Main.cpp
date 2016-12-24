#include "Application.h"
#include "Util/Display.h"

#include "Util/Noise_Generator.h"

#include<iostream>
#include<string>

int main()
{
    Display::create("MattCraft");

    Application app;
    app.runMainLoop();

    return EXIT_SUCCESS;
}











