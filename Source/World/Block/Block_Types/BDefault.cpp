#include "BDefault.h"

#include "../../Generators/GStructures.h"

#include <iostream>

namespace Block
{
    Default::Default(const std::string& dataFileName)
    :   Type (dataFileName)
    {}

    BSand::BSand()
    :   Type ("Sand")
    {

    }

    void BSand::tick(World& world, const Position& pos)
    {
        //std::cout << "Sand tick\n";
    }

}
