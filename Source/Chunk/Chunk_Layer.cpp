#include "Chunk_Layer.h"

#include "D_Blocks.h"

#include "Chunk.h"

Chunk_Layer::Chunk_Layer()
:   m_blocks (Chunk::SIZE * Chunk::SIZE)
{
    //Fill up the vector with air
    for (auto i = 0 ; i < Chunk::SIZE * Chunk::SIZE ; i++ ) {
        m_blocks.at(i) = &Block::air;
    }
}

const Block::Block_Base& Chunk_Layer::getBlock(const Vector2& location) const
{
    return *m_blocks.at(Chunk::SIZE * location.x + location.y);
}

void Chunk_Layer::setBlock (Block::Block_Base& block, const Vector2& location)
{
    if (block.getID() != Block::Id::Air) {
        m_blockCount++;
        m_isEmpty = false;
    } else {
        m_blockCount --;
        if (!m_blockCount) m_isEmpty = true;
    }
    m_blocks.at(Chunk::SIZE * location.x + location.y) = &block;
}

