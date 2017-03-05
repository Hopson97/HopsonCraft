#include <iostream>
#include <fstream>

#include "Display.h"
#include "Application.h"
#include "Util/Random.h"
#include "Util/Config.h"
#include "Util/ConfigParser.h"
#include "Util/Singleton.h"

#include "World/Block/Block_Database.h"

namespace
{
    void initilize()
    {
        Random  ::init();
        Display ::init();

        Block::Database::get();
    }

    void loadConfig()
    {
        const std::string fileName = "HopsonCraft.conf";
        std::ifstream inFile (fileName);

        if(inFile.is_open())
        {
            Singleton<Config>::get().loadFromStream(fileName, inFile);
        }
    }
}

int main() try
{
    initilize();
    //loadConfig();

    Application app;
    app.runMainGameLoop();

    return 0;
}
catch(std::exception& e)
{
    std::cout << e.what() << std::endl;
    std::cin.ignore();
}


