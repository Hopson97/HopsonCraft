#include "D_Blocks.h"

#include <map>

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

    std::map<Block::ID, Block_t*> blockMap;

    void initBlockDatabase()
    {
        blockMap[Block::ID::Air]            = &air;
        blockMap[Block::ID::Grass]          = &grass;
        blockMap[Block::ID::Dirt]           = &dirt;
        blockMap[Block::ID::Stone]          = &stone;
        blockMap[Block::ID::Sand]           = &sand;
        blockMap[Block::ID::Water]          = &water;
        blockMap[Block::ID::Oak_Leaf]       = &oakLeaf;
        blockMap[Block::ID::Oak_Wood]       = &oakWood;
        blockMap[Block::ID::Oak_Plank]      = &oakPlank;
        blockMap[Block::ID::Glass]          = &glass;
        blockMap[Block::ID::Cobble_Stone]   = &cobbleStone;
        blockMap[Block::ID::Stone_Brick]    = &stoneBricks;
        blockMap[Block::ID::Snow]           = &snow;
        blockMap[Block::ID::Cactus]         = &cactus;
        blockMap[Block::ID::Rose]           = &rose;
        blockMap[Block::ID::Tall_Grass]     = &tallGrass;
        blockMap[Block::ID::Dead_Shrub]     = &deadShrub;
        blockMap[Block::ID::Bedrock]        = &bedrock;
    }

    Block_t& getBlockFromId (Block::ID id)
    {
        return *blockMap.at(id);
    }
}
