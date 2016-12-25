#ifndef D_BLOCKS_H_INCLUDED
#define D_BLOCKS_H_INCLUDED

#include <cstdint>

#include "Block_Type/Block_Types.h"
#include "Block_Enums.h"

namespace Block
{
    extern Block::Air           air;
    extern Block::Grass         grass;
    extern Block::Dirt          dirt;
    extern Block::Stone         stone;
    extern Block::Water         water;
    extern Block::Sand          sand;
    extern Block::Oak_Leaf      oakLeaf;
    extern Block::Oak_Wood      oakWood;
    extern Block::Oak_Plank     oakPlank;
    extern Block::Glass         glass;
    extern Block::Cobblestone   cobbleStone;
    extern Block::Stone_Brick   stoneBricks;
    extern Block::Snow          snow;
    extern Block::Cactus        cactus;
    extern Block::Rose          rose;
    extern Block::Tall_Grass    tallGrass;
    extern Block::Dead_Shrub    deadShrub;
    extern Block::Bedrock       bedrock;
    extern Block::Oak_Sapling   oakSapling;

    void initBlockDatabase ();

    Block::Block_Type& get (Block::ID id);
    Block::Block_Type& get (uint8_t   id);
}

#endif // D_BLOCKS_H_INCLUDED
