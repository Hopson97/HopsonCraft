#include "Nodes.h"

#include "../Block/Block_Database.h"

//Blocks

CBlock::CBlock(Block_t ID, uint8_t meta)
:   id          {ID}
,   metaData    {meta}
{ }

CBlock::CBlock()
:   id          {0}
,   metaData    {0}
{ }

CBlock::CBlock(Block_t t)
:   id          {t}
,   metaData    {0}
{ }

CBlock::CBlock(Block::ID newID)
:   id          {static_cast<Block_t>(newID)}
,   metaData    {0}
{ }

const Block::Data_Holder& CBlock::getData() const
{
    return getType().getData().get();
}

const Block::Type& CBlock::getType() const
{
    return Block::Database::get().getBlock(id);
}

//Light
CLight::CLight()
:   natural    (MAX_LIGHT)
,   block      (0)
{ }
