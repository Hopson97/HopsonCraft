#ifndef D_BLOCKS_H_INCLUDED
#define D_BLOCKS_H_INCLUDED

#include <cstdint>

#include "Block_Type/Block_Types.h"
#include "Block_Enums.h"

namespace Block
{
    void initBlockDatabase ();

    Block::Block_Type& get (Block::ID id);
    Block::Block_Type& get (uint8_t   id);
}

#endif // D_BLOCKS_H_INCLUDED
