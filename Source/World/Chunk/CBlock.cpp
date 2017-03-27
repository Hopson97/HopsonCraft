#include "CBlock.h"

#include "../Block/Block_Database.h"

CBlock::CBlock()
:   id  (0)
{ }

CBlock::CBlock(Block_t t)
:   id  (t)
{ }

CBlock::CBlock(Block::ID newID)
:   id  (static_cast<Block_t>(newID))
{ }

const Block::Data_Holder& CBlock::getData() const
{
    return getType().getData().get();
}

const Block::Type& CBlock::getType() const
{
    return Block::Database::get().getBlock(id);
}
