#include "D_Blocks.h"

#include <vector>
#include <cstdint>

using u32 = uint32_t;

namespace Block
{
    Block::Block_Data air         ("Air");
    Block::Block_Data grass       ("Grass");
    Block::Block_Data dirt        ("Dirt");
    Block::Block_Data stone       ("Stone");
    Block::Block_Data water       ("Water");
    Block::Block_Data sand        ("Sand");
    Block::Block_Data oakLeaf     ("Oak_Leaf");
    Block::Block_Data oakWood     ("Oak_Wood");
    Block::Block_Data oakPlank    ("Oak_Plank");
    Block::Block_Data glass       ("Glass");
    Block::Block_Data cobbleStone ("Cobblestone");
    Block::Block_Data stoneBricks ("Stone_Bricks");
    Block::Block_Data snow        ("Snow");
    Block::Block_Data cactus      ("Cactus");
    Block::Block_Data rose        ("Rose");
    Block::Block_Data tallGrass   ("Tall_Grass");
    Block::Block_Data deadShrub   ("Dead_Shrub");
    Block::Block_Data bedrock     ("Bedrock");

    std::vector<Block::Block_Data*> blocks((u32)Block::ID::NUM_BLOCK_TYPES);

    void initBlockDatabase()
    {
        blocks[(u32)Block::ID::Air      ]   = &air;
        blocks[(u32)Block::ID::Grass    ]   = &grass;
        blocks[(u32)Block::ID::Dirt     ]   = &dirt;
        blocks[(u32)Block::ID::Stone    ]   = &stone;
        blocks[(u32)Block::ID::Sand     ]   = &sand;
        blocks[(u32)Block::ID::Water    ]   = &water;
        blocks[(u32)Block::ID::Oak_Leaf ]   = &oakLeaf;
        blocks[(u32)Block::ID::Oak_Wood ]   = &oakWood;
        blocks[(u32)Block::ID::Oak_Plank]   = &oakPlank;
        blocks[(u32)Block::ID::Glass    ]   = &glass;
        blocks[(u32)Block::ID::Cobble_Stone ]   = &cobbleStone;
        blocks[(u32)Block::ID::Stone_Brick  ]   = &stoneBricks;
        blocks[(u32)Block::ID::Snow     ]   = &snow;
        blocks[(u32)Block::ID::Cactus   ]   = &cactus;
        blocks[(u32)Block::ID::Rose     ]   = &rose;
        blocks[(u32)Block::ID::Tall_Grass   ]   = &tallGrass;
        blocks[(u32)Block::ID::Dead_Shrub   ]   = &deadShrub;
        blocks[(u32)Block::ID::Bedrock      ]   = &bedrock;
    }

    Block::Block_Data& get (Block::ID id)
    {
        return *blocks.at((u32)id);
    }
}
