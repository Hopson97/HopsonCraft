#include "Chunk_Layer.h"

#include <iostream>

#include "Chunk.h"
#include "../Block/D_Blocks.h"
#include "../World.h"

Chunk_Layer::Chunk_Layer()
{
    for (auto x = 0 ; x < World::CHUNK_SIZE ; x++)
    {
        for (auto z = 0 ; z < World::CHUNK_SIZE ; z++)
        {
            m_blocks[World::CHUNK_SIZE * z + x] = 0; //0 is air
        }
    }
}

void Chunk_Layer::setBlock(int x, int z, const Block::Block_Type& block)
{
    if(!block.getData().isOpaque())
    {
        m_translucentCount++;
    }
    else
    {
        m_translucentCount--;
    }

    m_blocks[World::CHUNK_SIZE * z + x] = (uint8_t)block.getData().getID();
}

const Block::Block_Type& Chunk_Layer::getBlock(int x, int z) const
{
    return Block::get((Block::ID)(m_blocks[World::CHUNK_SIZE * z + x]));
}

bool Chunk_Layer::hasTranslucentBlocks() const
{
    return m_translucentCount > 0;
}

