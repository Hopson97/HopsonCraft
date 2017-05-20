#include "GTrees.h"

#include "../Chunk/CNodes.h"
#include "../IBlock_Accessible.h"

void makeOakTree(IBlock_Accessible& access,
                 const Block::Position& pos,
                 Random::Generator<std::mt19937>& random)
{
    CBlock airBlock  = Block::ID::Air;
    CBlock leafBlock = Block::ID::Oak_Leaf;
    CBlock woodBlock = Block::ID::Oak_Wood;

    std::vector<Block::Position> airPositions;
    std::vector<Block::Position> woodPositions;
    std::vector<Block::Position> leafPositions;

    int height      = Random::intInRange(5, 8);
    int crownSize   = 2;

    for (int32_t zLeaf = -crownSize; zLeaf <= crownSize; zLeaf++)
    for (int32_t xLeaf = -crownSize; xLeaf <= crownSize; xLeaf++)
    {
        leafPositions.emplace_back(pos.x + xLeaf, pos.y + height - 1,   pos.z + zLeaf);
        leafPositions.emplace_back(pos.x + xLeaf, pos.y + height,       pos.z + zLeaf);
    }

    for (int32_t zLeaf = -crownSize + 1; zLeaf <= crownSize - 1; zLeaf++)
    {
        leafPositions.emplace_back(pos.x, pos.y + height + 1, pos.z + zLeaf);
    }

    for (int32_t xLeaf = -crownSize + 1; xLeaf <= crownSize - 1; xLeaf++)
    {
        leafPositions.emplace_back(pos.x + xLeaf, pos.y + height + 1, pos.z);
    }

    int h = pos.y + height;
    airPositions.emplace_back(pos.x + crownSize, h, pos.z + crownSize);
    airPositions.emplace_back(pos.x - crownSize, h, pos.z + crownSize);
    airPositions.emplace_back(pos.x + crownSize, h, pos.z - crownSize);
    airPositions.emplace_back(pos.x - crownSize, h, pos.z - crownSize);
    leafPositions.emplace_back(pos.x, pos.y + height + 2, pos.z);

    for (int y = 1; y < height; y++)
    {
        woodPositions.emplace_back(pos.x, pos.y + y, pos.z);
    }

    for (auto& leaf : leafPositions)
    {
        access.setBlock(leaf.x, leaf.y, leaf.z, leafBlock);
    }

    for (auto& wood : woodPositions)
    {
        access.qSetBlock(wood.x, wood.y, wood.z, woodBlock);
    }

    for (auto& air : airPositions)
    {
        access.setBlock(air.x, air.y, air.z, airBlock);
    }
}

void makePalmTree(IBlock_Accessible& access,
                  const Block::Position& pos,
                  Random::Generator<std::mt19937>& random)
{
    CBlock airBlock  = Block::ID::Air;
    CBlock leafBlock = Block::ID::Oak_Leaf;
    CBlock woodBlock = Block::ID::Oak_Wood;

    std::vector<Block::Position> airPositions;
    std::vector<Block::Position> woodPositions;
    std::vector<Block::Position> leafPositions;

    int height      = Random::intInRange(5, 8);
    int crownSize   = Random::intInRange(4, 6);

    for (int x = -crownSize; x <= crownSize; x++)
    {
        leafPositions.emplace_back(pos.x + x, pos.y + height, pos.z);
    }
    for (int z = -crownSize; z <= crownSize; z++)
    {
        leafPositions.emplace_back(pos.x, pos.y + height, pos.z + z);
    }

    for (int32_t zLeaf = -1; zLeaf <= 1; zLeaf++)
    for (int32_t xLeaf = -1; xLeaf <= 1; xLeaf++)
    {
        leafPositions.emplace_back(pos.x + xLeaf, pos.y + height - 1, pos.z + zLeaf);
        leafPositions.emplace_back(pos.x + xLeaf, pos.y + height    , pos.z + zLeaf);
    }

    leafPositions.emplace_back(pos.x,             pos.y + height - 1, pos.z + crownSize);
    leafPositions.emplace_back(pos.x,             pos.y + height - 1, pos.z - crownSize);
    leafPositions.emplace_back(pos.x + crownSize, pos.y + height - 1, pos.z );
    leafPositions.emplace_back(pos.x - crownSize, pos.y + height - 1, pos.z );
    leafPositions.emplace_back(pos.x,             pos.y + height + 1, pos.z );

    for (int32_t y = 1; y < height; y++)
    {
        woodPositions.emplace_back(pos.x, pos.y + y, pos.z);
    }

    for (auto& leaf : leafPositions)
    {
        access.setBlock(leaf.x, leaf.y, leaf.z, leafBlock);
    }

    for (auto& wood : woodPositions)
    {
        access.qSetBlock(wood.x, wood.y, wood.z, woodBlock);
    }

    for (auto& air : airPositions)
    {
        access.setBlock(air.x, air.y, air.z, airBlock);
    }
}





































