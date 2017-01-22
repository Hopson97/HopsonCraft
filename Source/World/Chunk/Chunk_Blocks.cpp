#include "Chunk_Blocks.h"

#include <iostream>

#include "../Block/D_Blocks.h"
#include "../World.h"
#include "../World_Constants.h"

#include "Chunk.h"
#include "Chunk_Map.h"

Chunk_Blocks::Chunk_Blocks(Chunk& chunk,
                           const Chunk_Location& location,
                           Chunk_Map& chunkMap)
:   m_p_chunk       (&chunk)
,   m_location      (location)
,   m_p_chunkMap    (&chunkMap)
,   m_maxHeights    (World_Constants::CHUNK_AREA)
{ }

void Chunk_Blocks::setBlock(const Block_Location& location,
                            uint8_t block,
                            bool overrideBlocks)
{
    if ( location.x < 0 )           return;
    else if ( location.z < 0 )      return;
    else if ( location.x >= World_Constants::CHUNK_SIZE )  return;
    else if ( location.z >= World_Constants::CHUNK_SIZE )  return;
    else
        qSetBlock(location, block, overrideBlocks);

}

void Chunk_Blocks::qSetBlock(const Block_Location& location,
                             uint8_t block,
                             bool overrideBlocks)
{
    if ((unsigned)location.y > m_layers.size() - 1)
        return;

    if (m_layers[location.y].getBlock(location.x, location.z).getData().getID() == Block::ID::Air || overrideBlocks)
    {
        if(m_lightSources.find(location) != m_lightSources.end())
        {
            m_lightSources.erase(location);
        }

        //Bottom layer is indestructable
        if (m_p_chunk->hasBlockData() && location.y == 0)
        {
                return;
        }
        if (Block::get(block).getData().getLightEmission() > 0)
        {
            m_lightSources[location] = (uint8_t)Block::get(block).getData().getLightEmission();
        }

        m_layers[location.y].setBlock(location.x, location.z, Block::get(block));
    }
}

const Block::Block_Type& Chunk_Blocks::getBlock (const Block_Location& location) const
{
    if (location.y > World_Constants::CHUNK_HEIGHT)
        return Block::get(Block::ID::Air);

    if (location.x == -1 )
    {
        return getAdjacentChunkBlock(-1, 0, {World_Constants::CHUNK_SIZE - 1, location.y, location.z});
    }
    else if (location.z == -1 )
    {
        return getAdjacentChunkBlock(0, -1, {location.x, location.y, World_Constants::CHUNK_SIZE - 1});
    }
    else if (location.x == World_Constants::CHUNK_SIZE )
    {
        return getAdjacentChunkBlock(1, 0, {0, location.y, location.z});
    }
    else if (location.z == World_Constants::CHUNK_SIZE )
    {
        return getAdjacentChunkBlock(0, 1, {location.x, location.y, 0});
    }
    else if ((unsigned)location.y > m_layers.size() - 1)
    {
        return Block::get(Block::ID::Air);
    }
    else if (location.y < 0)
    {
        return Block::get(Block::ID::Air);
    }
    else
    {
        return m_layers[location.y].getBlock(location.x, location.z);
    }
    return Block::get(Block::ID::Air);    //This is for world edges
}

void Chunk_Blocks::calculateChunkLight()
{
    for (auto& lightSouce : m_lightSources)
    {
        auto& l = lightSouce.first;
        floodBlockLight(l.x, l.y, l.z, lightSouce.second);
    }


    //Sunlight hits every block above the maximum height of a chunk column
    for (int x = 0 ; x < World_Constants::CHUNK_SIZE ; ++x)
    {
        for (int z = 0 ; z < World_Constants::CHUNK_SIZE ; ++z)
        {
            //for (int y = getMaxheightAt(x, z) ; y < m_layers.size() - 1 ; ++y)
            {
                floodNaturalLight(x, getMaxheightAt(x, z) + 1, z, World_Constants::MAX_LIGHT_VALUE);
            }
        }
    }
}

void Chunk_Blocks::calculateChunkEdgeLight()
{
    //Chunk edges
    for (int y = 0 ; y < m_layers.size() - 1 ; ++y )
    {
        for (int x = 0 ; x < World_Constants::CHUNK_SIZE ; ++x)
        {
            floodNaturalLight(x, y, 0, m_p_chunk->getAdjBlocks(0, -1)->getLayer(y).getNaturalLight(x, World_Constants::CHUNK_SIZE - 1));
            floodNaturalLight(x, y, World_Constants::CHUNK_SIZE - 1, m_p_chunk->getAdjBlocks(0, 1)->getLayer(y).getNaturalLight(x, 0));

            floodBlockLight(x, y, 0, m_p_chunk->getAdjBlocks(0, -1)->getLayer(y).getBlockLight(x, World_Constants::CHUNK_SIZE - 1));
            floodBlockLight(x, y, World_Constants::CHUNK_SIZE - 1, m_p_chunk->getAdjBlocks(0, 1)->getLayer(y).getBlockLight(x, 0));
        }

        for (int z = 0 ; z < World_Constants::CHUNK_SIZE ; ++z)
        {
            floodNaturalLight(0, y, z, m_p_chunk->getAdjBlocks(-1, 0)->getLayer(y).getNaturalLight(World_Constants::CHUNK_SIZE - 1, z));
            floodNaturalLight(World_Constants::CHUNK_SIZE - 1, y, z, m_p_chunk->getAdjBlocks(1, 0)->getLayer(y).getNaturalLight(0, z));

            floodBlockLight(0, y, z, m_p_chunk->getAdjBlocks(-1, 0)->getLayer(y).getBlockLight(World_Constants::CHUNK_SIZE - 1, z));
            floodBlockLight(World_Constants::CHUNK_SIZE - 1, y, z, m_p_chunk->getAdjBlocks(1, 0)->getLayer(y).getBlockLight(0, z));
        }
    }
}

void Chunk_Blocks::resetLight()
{
    for (auto& layer : m_layers)
    {
        layer.resetLight();
    }
}

//Recurssive "flood fill" algoritm for light
void Chunk_Blocks::floodNaturalLight(int x, int y, int z, uint8_t value)
{
    if (x < 0)
    {
        return;
    }

    if (x > World_Constants::CHUNK_SIZE - 1)
        return;

    if (z < 0)
        return;

    if (z > World_Constants::CHUNK_SIZE - 1)
        return;

    if (y > World_Constants::CHUNK_HEIGHT)
        return;

    auto change = m_layers[y].getBlock(x, z).getData().getLightChange();
    if (change < 0)
        return;

    auto light = (int)value;
    light -= change;
    if (light < 0)
        return;

    value -= (uint8_t)change;

    if (m_layers[y].getNaturalLight(x, z) >= value)
        return;

    if (value == 0)
        return;

    m_layers[y].setNaturalLight(x, z, value--);

    floodNaturalLight(x - 1,    y,      z,      value);
    floodNaturalLight(x + 1,    y,      z,      value);
    floodNaturalLight(x,        y + 1,  z,      value);
    floodNaturalLight(x,        y - 1,  z,      value);
    floodNaturalLight(x,        y,      z + 1,  value);
    floodNaturalLight(x,        y,      z - 1,  value);
}

//Recurssive "flood fill" algoritm for light
void Chunk_Blocks::floodBlockLight(int x, int y, int z, uint8_t value)
{
    if (x < 0)
        return;

    if (x > World_Constants::CHUNK_SIZE - 1)
        return;

    if (z < 0)
        return;

    if (z > World_Constants::CHUNK_SIZE - 1)
        return;

    if (y > World_Constants::CHUNK_HEIGHT)
        return;

    auto change = m_layers[y].getBlock(x, z).getData().getLightChange();
    if (change < 0)
        return;

    auto light = (int)value;

    light -= change;
    if (light < 0)
        return;

    value -= (uint8_t)change;

    if (m_layers[y].getBlockLight(x, z) >= value)
        return;

    if (value == 0)
        return;

    m_layers[y].setBlockLight(x, z, value--);

    floodBlockLight(x - 1,    y,      z,      value);
    floodBlockLight(x + 1,    y,      z,      value);
    floodBlockLight(x,        y + 1,  z,      value);
    floodBlockLight(x,        y - 1,  z,      value);
    floodBlockLight(x,        y,      z + 1,  value);
    floodBlockLight(x,        y,      z - 1,  value);
}

const Block::Block_Type& Chunk_Blocks::getAdjacentChunkBlock (int xChange,
                                                              int zChange,
                                                              const Block_Location& location) const
{
    //Try dd a chunk incase it does not yet exist
    Chunk_Location chunkLocation (m_location.x + xChange, m_location.z + zChange);
    m_p_chunkMap->addChunk(chunkLocation);

    //Return the respective block...
    return m_p_chunkMap->getChunkAt(chunkLocation)->getBlocks().getBlock(location);
}

size_t Chunk_Blocks::getLayerCount() const
{
    return m_layers.size();
}

const Chunk_Layer& Chunk_Blocks::getLayer(uint32_t layer) const
{
    return m_layers[layer];
}

bool Chunk_Blocks::layerHasTranslucentBlocks(uint32_t layer) const
{
    if (layer > m_layers.size() - 1)
        return true;
    else
        return getLayer(layer).hasTranslucentBlocks();
}

void Chunk_Blocks::calculateMaxHeights()
{
    for (auto x = 0 ; x < World_Constants::CHUNK_SIZE ; ++x)    //z
    {
        for (auto z = 0 ; z < World_Constants::CHUNK_SIZE ; ++z)    //x
        {
            recalculateMaxHeight(x, z);
        }
    }
}

void Chunk_Blocks::recalculateMaxHeight(int x, int z)
{
    for (auto y = int(m_layers.size() - 1) ; y > 0 ; y--)
    {
        if (m_layers[y].getBlock(x, z).getData().getID() != Block::ID::Air)
        {
            m_maxHeights[x * World_Constants::CHUNK_SIZE + z] = y;
            break;
        }
    }
}

int Chunk_Blocks::getMaxheightAt(int x, int z) const
{
    return m_maxHeights[x * World_Constants::CHUNK_SIZE + z];
}


