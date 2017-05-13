#include "BPlant.h"

#include "../../World.h"

#include <iostream>

namespace Block
{
    BPlant::BPlant(const std::string& name)
    :   Type (name)
    { }

    void BPlant::trigger(World& world, const Position& position) const
    {
        auto block = world.getBlock({position.x, position.y - 1, position.z});
        if (block == Block::ID::Air)
        {
            world.setBlock({position.x, position.y, position.z}, 0);
        }
    }
}
