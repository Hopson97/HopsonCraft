#ifndef D_BLOCKS_H_INCLUDED
#define D_BLOCKS_H_INCLUDED

#include "Block_Data.h"
#include "Block_Enums.h"

namespace Block
{
    extern Block::Block_Data air;
    extern Block::Block_Data grass;
    extern Block::Block_Data dirt;
    extern Block::Block_Data stone;
    extern Block::Block_Data water;
    extern Block::Block_Data sand;
    extern Block::Block_Data oakLeaf;
    extern Block::Block_Data oakWood;
    extern Block::Block_Data oakPlank;
    extern Block::Block_Data glass;
    extern Block::Block_Data cobbleStone;
    extern Block::Block_Data stoneBricks;
    extern Block::Block_Data snow;
    extern Block::Block_Data cactus;
    extern Block::Block_Data rose;
    extern Block::Block_Data tallGrass;
    extern Block::Block_Data deadShrub;
    extern Block::Block_Data bedrock;

    void initBlockDatabase ();

    Block::Block_Data& get (Block::ID id);
}

#endif // D_BLOCKS_H_INCLUDED
