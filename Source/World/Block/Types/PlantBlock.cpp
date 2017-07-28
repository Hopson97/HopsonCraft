#include "PlantBlock.h"

#include "../../World.h"


PlantBlock::PlantBlock(std::string&& name)
:   BlockType (std::move(name))
{ }

void PlantBlock::trigger(World& world, CBlock& cBlock, const BlockPosition& position) const
{

}

