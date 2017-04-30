#ifndef GSTRUCTURES_H_INCLUDED
#define GSTRUCTURES_H_INCLUDED

#include "../../Util/Random.h"
#include "../Block/Block_Position.h"

/*
    Q: What is the template "Access"?

    A: Access is the way this function is able to reach functions such as "setBlock" and "qSetBlock",
    as this can be done in multiple areas.

    For example, if you make a tree during generation, then it just uses a "Full_Chunk"

    But, if a tree is grown from a sapling (As of 30/04/2017, this is not in the game), then it
    uses the "world" to access these functions.

    The reason being is that the world set blocks functions will add a changed chunk into a chunk
    rebuild std::vector, which is very handy!
*/

template<typename Access, typename Rand>
void makeOakTree(Access& access,
                 const Block::Position& pos,
                 Random::Generator<Rand> random)
{
    auto height = random.intInRange(4, 6);
    int32_t crownSize = 2;

    for (int32_t zLeaf = -crownSize; zLeaf <= crownSize; zLeaf++)
    {
        for (int32_t xLeaf = -crownSize; xLeaf <= crownSize; xLeaf++)
        {
            access.setBlock({pos.x + xLeaf, pos.y + height - 1, pos.z + zLeaf}, Block::ID::Oak_Leaf);
            access.setBlock({pos.x + xLeaf, pos.y + height + 0, pos.z + zLeaf}, Block::ID::Oak_Leaf);
        }
    }

    auto h = pos.y + height;
    access.setBlock({pos.x + crownSize, h, pos.z + crownSize}, Block::ID::Air);
    access.setBlock({pos.x - crownSize, h, pos.z + crownSize}, Block::ID::Air);
    access.setBlock({pos.x + crownSize, h, pos.z - crownSize}, Block::ID::Air);
    access.setBlock({pos.x - crownSize, h, pos.z - crownSize}, Block::ID::Air);

    for (int32_t zLeaf = -crownSize + 1; zLeaf <= crownSize - 1; zLeaf++)
    {
        int32_t xLeaf = 0;
        access.setBlock({pos.x + xLeaf, pos.y + height + 1, pos.z + zLeaf}, Block::ID::Oak_Leaf);
    }

    for (int32_t zLeaf = -crownSize + 1; zLeaf <= crownSize - 1; zLeaf++)
    {
        int32_t xLeaf = 0;
        access.setBlock({pos.x + zLeaf, pos.y + height + 1, pos.z + xLeaf}, Block::ID::Oak_Leaf);
    }

    access.setBlock({pos.x, pos.y + height + 2, pos.z}, Block::ID::Oak_Leaf);

    for (int32_t y = 1; y < height; y++)
    {
        access.qSetBlock({pos.x, pos.y + y, pos.z}, Block::ID::Oak_Wood);
    }
}

#endif // GSTRUCTURES_H_INCLUDED
