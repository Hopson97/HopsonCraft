#include "D_Blocks.h"

#include <vector>
#include <cstdint>
#include <cassert>

using u32 = uint32_t;

namespace Block
{
    Block::Air          air;
    Block::Grass        grass;
    Block::Dirt         dirt;
    Block::Stone        stone;
    Block::Water        water;
    Block::Sand         sand;
    Block::Oak_Leaf     oakLeaf;
    Block::Oak_Wood     oakWood;
    Block::Oak_Plank    oakPlank;
    Block::Glass        glass;
    Block::Cobblestone  cobbleStone;
    Block::Stone_Brick  stoneBricks;
    Block::Snow         snow;
    Block::Cactus       cactus;
    Block::Rose         rose;
    Block::Tall_Grass   tallGrass;
    Block::Dead_Shrub   deadShrub;
    Block::Bedrock      bedrock;
    Block::Oak_Sapling  oakSapling;

    std::vector<Block::Block_Type*> blocks((u32)Block::ID::NUM_BLOCK_TYPES);

    void initBlockDatabase()
    {
        blocks[(u32)Block::ID::Air          ]   = &air;
        blocks[(u32)Block::ID::Grass        ]   = &grass;
        blocks[(u32)Block::ID::Dirt         ]   = &dirt;
        blocks[(u32)Block::ID::Stone        ]   = &stone;
        blocks[(u32)Block::ID::Sand         ]   = &sand;
        blocks[(u32)Block::ID::Water        ]   = &water;
        blocks[(u32)Block::ID::Oak_Leaf     ]   = &oakLeaf;
        blocks[(u32)Block::ID::Oak_Wood     ]   = &oakWood;
        blocks[(u32)Block::ID::Oak_Plank    ]   = &oakPlank;
        blocks[(u32)Block::ID::Glass        ]   = &glass;
        blocks[(u32)Block::ID::Cobble_Stone ]   = &cobbleStone;
        blocks[(u32)Block::ID::Stone_Brick  ]   = &stoneBricks;
        blocks[(u32)Block::ID::Snow         ]   = &snow;
        blocks[(u32)Block::ID::Cactus       ]   = &cactus;
        blocks[(u32)Block::ID::Rose         ]   = &rose;
        blocks[(u32)Block::ID::Tall_Grass   ]   = &tallGrass;
        blocks[(u32)Block::ID::Dead_Shrub   ]   = &deadShrub;
        blocks[(u32)Block::ID::Bedrock      ]   = &bedrock;
        blocks[(u32)Block::ID::Oak_Sapling  ]   = &oakSapling;

        assert(blocks.size() == (int)Block::ID::NUM_BLOCK_TYPES);
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
