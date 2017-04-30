#ifndef GSTRUCTURES_H_INCLUDED
#define GSTRUCTURES_H_INCLUDED

#include "../../Util/Random.h"
#include "../Block/Block_Position.h"

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
