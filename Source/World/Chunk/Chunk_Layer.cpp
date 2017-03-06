#include "Chunk_Layer.h"

#include <iostream>

#include "Chunk.h"
#include "../Block/D_Blocks.h"
#include "../World.h"

Chunk_Layer::Chunk_Layer()
{
    for (int i = 0 ; i < World_Constants::CHUNK_AREA ; i++)
    {
        m_blockLightMap[i] = 0;
        m_naturalLightMap[i] = 0;
        m_blocks[i] = 0;
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

    m_blocks[World_Constants::CHUNK_SIZE * z + x] = (uint8_t)block.getData().getID();
}

const Block::Block_Type& Chunk_Layer::getBlock(int x, int z) const
{
    return Block::get((Block::ID)(m_blocks[World_Constants::CHUNK_SIZE * z + x]));
}

uint8_t Chunk_Layer::getNaturalLight(int x, int z) const
{
    return m_naturalLightMap[World_Constants::CHUNK_SIZE * z + x];
}

uint8_t Chunk_Layer::getBlockLight(int x, int z) const
{
    return m_blockLightMap[World_Constants::CHUNK_SIZE * z + x];
}

void Chunk_Layer::setNaturalLight(int x, int z, uint8_t value)
{
    m_naturalLightMap[World_Constants::CHUNK_SIZE * z + x] = value;
}

void Chunk_Layer::setBlockLight(int x, int z, uint8_t value)
{
    m_blockLightMap[World_Constants::CHUNK_SIZE * z + x] = value;
}

void Chunk_Layer::resetLight()
{
    for (int i = 0 ; i < World_Constants::CHUNK_AREA ; i++)
    {
        m_blockLightMap     [i] = 0;
        m_naturalLightMap   [i] = 0;
    }
}


bool Chunk_Layer::hasTranslucentBlocks() const
{
    return m_translucentCount > 0;
}

