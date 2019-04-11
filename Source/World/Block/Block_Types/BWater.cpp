#include "BWater.h"

#include "../../World.h"

namespace Block
{
    BWater::BWater()
    :   Type ("Water")
    { }

    void BWater::trigger(World& world,
                         const Position& position) const
    {
/*
        auto block = world.getBlock({position.x, position.y - 1, position.z});
        if (block == Block::ID::Water)
            return;


        if(tryMove(world, position, { 0, -1,  0})) return;

        if(tryMove(world, position, { 1,  0,  0})) return;
        if(tryMove(world, position, {-1,  0,  0})) return;
        if(tryMove(world, position, { 0,  0,  1})) return;
        if(tryMove(world, position, { 0,  0, -1})) return;
*/
    }

    bool BWater::tryMove(World& world,
                         const Position& position,
                         const Position& vect) const
    {
        auto loc = position + vect;

        Vector3 blockPos{loc.x, loc.y, loc.z};

        auto block = world.getBlock(blockPos);

        if (block == 0)
        {
            world.setBlock({position.x, position.y, position.z}, Block::ID::Air);
            world.setBlock(blockPos, Block::ID::Water);
            return true;
        }
        return false;
    }

}
