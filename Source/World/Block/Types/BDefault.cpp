#include "BDefault.h"

#include "../../World.h"

namespace Block
{
    Default::Default(std::string&& dataFileName)
    :   BlockType (std::move(dataFileName))
    {}
}

