#ifndef GTREES_H_INCLUDED
#define GTREES_H_INCLUDED

#include "../../Util/Random.h"
#include "../Block/Block_Position.h"
#include "../Block/Block_ID.h"

//See GStructures.h for a definition of the args


template<typename Access, typename Rand>
void makeOakTree(Access& access,
                 const Block::Position& pos,
                 Random::Generator<Rand> random,
                 bool isMadeDuringWorldGen = true)
{
    auto height = random.intInRange(5, 8);
    int32_t crownSize = 2;

    for (int32_t zLeaf = -crownSize; zLeaf <= crownSize; zLeaf++)
    for (int32_t xLeaf = -crownSize; xLeaf <= crownSize; xLeaf++)
    {
        access.setBlock({pos.x + xLeaf, pos.y + height - 1, pos.z + zLeaf}, Block::ID::Oak_Leaf, isMadeDuringWorldGen);
        access.setBlock({pos.x + xLeaf, pos.y + height + 0, pos.z + zLeaf}, Block::ID::Oak_Leaf, isMadeDuringWorldGen);
    }


    auto h = pos.y + height;
    access.setBlock({pos.x + crownSize, h, pos.z + crownSize}, Block::ID::Air, isMadeDuringWorldGen);
    access.setBlock({pos.x - crownSize, h, pos.z + crownSize}, Block::ID::Air, isMadeDuringWorldGen);
    access.setBlock({pos.x + crownSize, h, pos.z - crownSize}, Block::ID::Air, isMadeDuringWorldGen);
    access.setBlock({pos.x - crownSize, h, pos.z - crownSize}, Block::ID::Air, isMadeDuringWorldGen);

    for (int32_t zLeaf = -crownSize + 1; zLeaf <= crownSize - 1; zLeaf++)
    {
        int32_t xLeaf = 0;
        access.setBlock({pos.x + xLeaf, pos.y + height + 1, pos.z + zLeaf}, Block::ID::Oak_Leaf, isMadeDuringWorldGen);
    }

    for (int32_t zLeaf = -crownSize + 1; zLeaf <= crownSize - 1; zLeaf++)
    {
        int32_t xLeaf = 0;
        access.setBlock({pos.x + zLeaf, pos.y + height + 1, pos.z + xLeaf}, Block::ID::Oak_Leaf, isMadeDuringWorldGen);
    }

    access.setBlock({pos.x, pos.y + height + 2, pos.z}, Block::ID::Oak_Leaf, isMadeDuringWorldGen);

    for (int32_t y = 1; y < height; y++)
    {
        access.qSetBlock({pos.x, pos.y + y, pos.z}, Block::ID::Oak_Wood, isMadeDuringWorldGen);
    }
}

template<typename Access, typename Rand>
void makeAcaciaTree(Access& access,
                 const Block::Position& pos,
                 Random::Generator<Rand> random,
                 bool isMadeDuringWorldGen = true)
{
    auto height = random.intInRange(5, 8);
    auto width1 = random.intInRange(4, 5);
    auto dir1 = random.intInRange(0, 1);

    for (int32_t y = 1; y < height; y++)
    {
        access.qSetBlock({pos.x, pos.y + y, pos.z}, Block::ID::Oak_Wood, isMadeDuringWorldGen);
    }

    float y = pos.y + height;
    switch(dir1)
    {
        case 0:
            for (int32_t i = 0; i <= width1; i++)
            {
                access.setBlock({pos.x, (int)std::floor(y), pos.z + i}, Block::ID::Oak_Wood, isMadeDuringWorldGen);
                y += 0.5;
            }
            break;

        case 1:
            for (int32_t i = 0; i <= width1; i++)
            {
                access.setBlock({pos.x + i, (int)std::floor(y), pos.z}, Block::ID::Oak_Wood, isMadeDuringWorldGen);
                y += 0.5;
            }
            break;
    }

    auto dir2 = random.intInRange(0, 1);

    for (int32_t y = 1; y < height; y++)
    {
        access.qSetBlock({pos.x, pos.y + y, pos.z}, Block::ID::Oak_Wood, isMadeDuringWorldGen);
    }

    y = pos.y + height;
    switch(dir2)
    {
        case 0:
            for (int32_t i = 0; i <= width1; i++)
            {
                access.setBlock({pos.x, (int)std::floor(y), pos.z - i}, Block::ID::Oak_Wood, isMadeDuringWorldGen);
                y += 0.5;
            }
            break;

        case 1:
            for (int32_t i = 0; i <= width1; i++)
            {
                access.setBlock({pos.x - i, (int)std::floor(y), pos.z}, Block::ID::Oak_Wood, isMadeDuringWorldGen);
                y += 0.5;
            }
            break;
    }

    ///@TODO Leaves
}

#endif // GTREES_H_INCLUDED
