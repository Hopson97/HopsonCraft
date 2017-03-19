#include "CBlock.h"

CBlock::CBlock()
:   id  (3)
{ }

CBlock::CBlock(Block_t t)
:   id  (t)
{ }

CBlock::CBlock(Block::ID id)
:   id  (static_cast<Block_t>(id))
{ }
