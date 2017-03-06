#include "Application.h"
#include "Util/Display.h"
#include "Util/Config.h"
#include "Util/Singleton.h"

#include "Util/Noise_Generator.h"

#include<iostream>
#include<string>
#include <fstream>

int main()
{
    // Initialise the configuration
    {
        std::string const filename = "HopsonCraft.conf";
        std::ifstream config_file(filename);
        if (config_file)
            Singleton<Config>::get().loadFromStream(filename, config_file);
    }

    Display::create("MattCraft");

    Application app;
    app.runMainLoop();

    return EXIT_SUCCESS;
}











