#include "CBlock.h"



CBlock::CBlock(Block_t t)
:   id  (t)
{ }

CBlock::CBlock(Block::ID id)
:   id  (static_cast<Block_t>(id))
{ }

bool operator == (CBlock left, Block::ID right)
{
    return left.id == static_cast<Block_t>(right);
}

