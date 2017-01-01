#include "Updatable_Block.h"

void Updatable_Block::setChunk(Chunk& chunk)
{
    m_p_chunk = &chunk;
}

void Updatable_Block::breakBlock()
{
    m_isDestroyed = true;
    onBreak();
}

bool Updatable_Block::isDestroyed() const
{
    return m_isDestroyed;
}
