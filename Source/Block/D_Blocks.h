#ifndef D_BLOCKS_H_INCLUDED
#define D_BLOCKS_H_INCLUDED

#include "Block/Block.h"
#include "Block/E_Block_ID.h"

namespace Block
{
    extern Block::Block_Base air;
    extern Block::Block_Base grass;
    extern Block::Block_Base dirt;
    extern Block::Block_Base stone;
    extern Block::Block_Base water;
    extern Block::Block_Base sand;
    extern Block::Block_Base oakLeaf;
    extern Block::Block_Base oakWood;
    extern Block::Block_Base oakPlank;
    extern Block::Block_Base glass;
    extern Block::Block_Base cobbleStone;
    extern Block::Block_Base stoneBricks;
    extern Block::Block_Base snow;
    extern Block::Block_Base cactus;

    void initBlockDatabase ();

    Block::Block_Base& getBlockFromId (Block::ID id);
}

#endif // D_BLOCKS_H_INCLUDED
