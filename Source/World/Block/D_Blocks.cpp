#include "D_Blocks.h"

#include <vector>
#include <cstdint>

using u32 = uint32_t;

namespace Block
{
    Block_t air         ("Air");
    Block_t grass       ("Grass");
    Block_t dirt        ("Dirt");
    Block_t stone       ("Stone");
    Block_t water       ("Water");
    Block_t sand        ("Sand");
    Block_t oakLeaf     ("Oak_Leaf");
    Block_t oakWood     ("Oak_Wood");
    Block_t oakPlank    ("Oak_Plank");
    Block_t glass       ("Glass");
    Block_t cobbleStone ("Cobblestone");
    Block_t stoneBricks ("Stone_Bricks");
    Block_t snow        ("Snow");
    Block_t cactus      ("Cactus");
    Block_t rose        ("Rose");
    Block_t tallGrass   ("Tall_Grass");
    Block_t deadShrub   ("Dead_Shrub");
    Block_t bedrock     ("Bedrock");

    std::vector<Block_t*> blocks((u32)Block::ID::NUM_BLOCK_TYPES);

    void initBlockDatabase()
    {
        blocks[(u32)Block::ID::Air]            = &air;
        blocks[(u32)Block::ID::Grass]          = &grass;
        blocks[(u32)Block::ID::Dirt]           = &dirt;
        blocks[(u32)Block::ID::Stone]          = &stone;
        blocks[(u32)Block::ID::Sand]           = &sand;
        blocks[(u32)Block::ID::Water]          = &water;
        blocks[(u32)Block::ID::Oak_Leaf]       = &oakLeaf;
        blocks[(u32)Block::ID::Oak_Wood]       = &oakWood;
        blocks[(u32)Block::ID::Oak_Plank]      = &oakPlank;
        blocks[(u32)Block::ID::Glass]          = &glass;
        blocks[(u32)Block::ID::Cobble_Stone]   = &cobbleStone;
        blocks[(u32)Block::ID::Stone_Brick]    = &stoneBricks;
        blocks[(u32)Block::ID::Snow]           = &snow;
        blocks[(u32)Block::ID::Cactus]         = &cactus;
        blocks[(u32)Block::ID::Rose]           = &rose;
        blocks[(u32)Block::ID::Tall_Grass]     = &tallGrass;
        blocks[(u32)Block::ID::Dead_Shrub]     = &deadShrub;
        blocks[(u32)Block::ID::Bedrock]        = &bedrock;
    }

    Block_t& get (Block::ID id)
    {
        return *blocks.at((u32)id);
    }
}
