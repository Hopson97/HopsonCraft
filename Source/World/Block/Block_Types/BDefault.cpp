#include "BDefault.h"

#include "../../Generators/GStructures.h"

#include <iostream>

#include "../../World.h"

namespace Block
{
    Default::Default(std::string&& dataFileName)
    :   Type (std::move(dataFileName))
    {}

    BSand::BSand()
    :   Type ("Sand")
    {}
}

