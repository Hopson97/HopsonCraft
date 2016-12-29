#include "D_Blocks.h"

#include <vector>
#include <cstdint>
#include <cassert>
#include <memory>

using u32 = uint32_t;

namespace Block
{
    std::vector<std::unique_ptr<Block_Type>> blocks((u32)Block::ID::NUM_BLOCK_TYPES);

    void registerBlock(std::unique_ptr<Block_Type> instance)
    {
        blocks[(u32)instance->getData().getID()] = std::move(instance);
    }

    void initBlockDatabase()
    {
        registerBlock(std::make_unique<Block::Air>          ());
        registerBlock(std::make_unique<Block::Grass>        ());
        registerBlock(std::make_unique<Block::Dirt>         ());
        registerBlock(std::make_unique<Block::Stone>        ());
        registerBlock(std::make_unique<Block::Sand>         ());
        registerBlock(std::make_unique<Block::Water>        ());
        registerBlock(std::make_unique<Block::Oak_Leaf>     ());
        registerBlock(std::make_unique<Block::Oak_Wood>     ());
        registerBlock(std::make_unique<Block::Oak_Plank>    ());
        registerBlock(std::make_unique<Block::Glass>        ());
        registerBlock(std::make_unique<Block::Cobblestone>  ());
        registerBlock(std::make_unique<Block::Stone_Brick>  ());
        registerBlock(std::make_unique<Block::Cactus>       ());
        registerBlock(std::make_unique<Block::Rose>         ());
        registerBlock(std::make_unique<Block::Tall_Grass>   ());
        registerBlock(std::make_unique<Block::Dead_Shrub>   ());
        registerBlock(std::make_unique<Block::Bedrock>      ());
        registerBlock(std::make_unique<Block::Oak_Sapling>  ());
        registerBlock(std::make_unique<Block::TNT>          ());
    }

    Block::Block_Type& get (Block::ID id)
    {
        return *blocks[(u32)id];
    }

    Block::Block_Type& get(uint8_t id)
    {
        return *blocks[(u32)id];
    }

}
