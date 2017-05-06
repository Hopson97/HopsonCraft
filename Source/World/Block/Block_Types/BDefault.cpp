#include "BDefault.h"

#include "../../Generators/GStructures.h"

#include <iostream>

#include "../../World.h"

namespace Block
{
    Default::Default(const std::string& dataFileName)
    :   Type (dataFileName)
    {}

    BSand::BSand()
    :   Type ("Sand")
    {
    }
}
