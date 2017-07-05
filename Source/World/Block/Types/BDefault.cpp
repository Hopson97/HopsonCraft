#include "BDefault.h"

#include "../../Generators/Structures.h"
#include "../../World.h"

namespace Block
{
    Default::Default(std::string&& dataFileName)
    :   BlockType (std::move(dataFileName))
    {}

    BSand::BSand()
    :   BlockType ("Sand")
    {}
}

