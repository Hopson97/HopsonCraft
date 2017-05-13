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

    BTall_Grass::BTall_Grass()
    :   Type ("Tall_Grass")
    {

    }

    void BTall_Grass::trigger(World& world, const Position& position) const
    {
        CBlock block = world.getBlock({position.x, position.y - 1, position.z});
        if (block.getData().blockID == Block::ID::Air)
        {
            world.setBlock({position.x, position.y, position.z}, 0);
        }
    }

}

