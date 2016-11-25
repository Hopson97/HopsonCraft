#include "Chunk_Layer.h"

#include "Chunk.h"
#include "../Block/D_Blocks.h"
#include "../World_Constants.h"

Chunk_Layer::Chunk_Layer()
{
    for (auto x = 0 ; x < World::CHUNK_SIZE ; x++)
    {
        for (auto z = 0 ; z < World::CHUNK_SIZE ; z++)
        {
            m_blocks.push_back(&Block::air);
        }
    }
}

void Chunk_Layer::setBlock(int x, int z, const Block_t& block)
{


    m_blocks.at(World::CHUNK_SIZE * z + x) = &block;
}

const Block_t& Chunk_Layer::getBlock(int x, int z) const
{
    return *m_blocks.at(World::CHUNK_SIZE * z + x);
}
