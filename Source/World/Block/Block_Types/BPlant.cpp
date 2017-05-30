#include "BPlant.h"

#include "../../World.h"

namespace Block
{
    BPlant::BPlant(std::string&& name)
    :   Type (std::move(name))
    { }

    void BPlant::trigger(World& world, CBlock& cBlock, const Position& position) const
    {
        auto block = world.getBlock({position.x, position.y - 1, position.z});
        if (block == Block::ID::Air)
        {
            world.setBlock({position.x, position.y, position.z}, 0);
        }
    }
}
