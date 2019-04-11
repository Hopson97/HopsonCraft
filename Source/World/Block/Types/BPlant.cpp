#include "BPlant.h"

#include "../../World.h"

namespace Block
{
    BPlant::BPlant(std::string&& name)
    :   Type (std::move(name))
    { }

    void BPlant::trigger(World& world, CBlock& cBlock, const Position& position) const
    {

    }
}
