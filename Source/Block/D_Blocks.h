#ifndef D_BLOCKS_H_INCLUDED
#define D_BLOCKS_H_INCLUDED

#include "Block/Block.h"
#include "Block/E_Block_ID.h"

namespace Block
{
    extern Block_t air;
    extern Block_t grass;
    extern Block_t dirt;
    extern Block_t stone;
    extern Block_t water;
    extern Block_t sand;
    extern Block_t oakLeaf;
    extern Block_t oakWood;
    extern Block_t oakPlank;
    extern Block_t glass;
    extern Block_t cobbleStone;
    extern Block_t stoneBricks;
    extern Block_t snow;
    extern Block_t cactus;
    extern Block_t rose;

    void initBlockDatabase ();

    Block_t& getBlockFromId (Block::ID id);
}

#endif // D_BLOCKS_H_INCLUDED
