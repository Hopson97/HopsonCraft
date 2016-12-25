#include "Chunk_Blocks.h"

#include "../Block/D_Blocks.h"
#include "../World_Constants.h"

#include "Chunk.h"
#include "Chunk_Map.h"

Chunk_Blocks::Chunk_Blocks(const Chunk& chunk,
                           const Chunk_Location& location,
                           Chunk_Map& chunkMap)
:   m_p_chunk       (&chunk)
,   m_location      (location)
,   m_p_chunkMap    (&chunkMap)
,   m_layers        (World::WATER_LEVEL + 1)
,   m_maxHeights    (World::CHUNK_SIZE * World::CHUNK_SIZE)
{ }

void Chunk_Blocks::setBlock(const Block_Location& location,
                            const Block::Block_Type& block,
                            bool overrideBlocks)
{
    if ( location.x < 0 )           return;
    else if ( location.z < 0 )      return;
    else if ( location.x >= World::CHUNK_SIZE )  return;
    else if ( location.z >= World::CHUNK_SIZE )  return;
    else
        qSetBlock(location, block, overrideBlocks);

}

void Chunk_Blocks::qSetBlock(const Block_Location& location,
                             const Block::Block_Type& block,
                             bool overrideBlocks)
{
    if ((unsigned)location.y > m_layers.size() - 1) addLayers(location.y);


    if (m_layers.at(location.y).getBlock(location.x, location.z).getData().getID() == Block::ID::Bedrock)
        return;


    if (m_layers.at(location.y).getBlock(location.x, location.z).getData().getID() == Block::ID::Air || overrideBlocks)
    {
        if (m_p_chunk->hasBlockData())
            m_addedBlocks[location] = (uint32_t)(block.getData().getID());

        m_layers.at(location.y).setBlock(location.x, location.z, block);
    }
}

const Block::Block_Type& Chunk_Blocks::getBlock (const Block_Location& location) const
{
    if (location.x == -1 )
    {
        return getAdjacentChunkBlock(-1, 0, {World::CHUNK_SIZE - 1, location.y, location.z});
    }
    else if (location.z == -1 )
    {
        return getAdjacentChunkBlock(0, -1, {location.x, location.y, World::CHUNK_SIZE - 1});
    }
    else if (location.x == World::CHUNK_SIZE )
    {
        return getAdjacentChunkBlock(1, 0, {0, location.y, location.z});
    }
    else if (location.z == World::CHUNK_SIZE )
    {
        return getAdjacentChunkBlock(0, 1, {location.x, location.y, 0});
    }
    else if ((unsigned)location.y > m_layers.size() - 1)
    {
        return Block::air;
    }
    else if (location.y < 0)
    {
        return Block::air;
    }
    else
    {
        return m_layers.at(location.y).getBlock(location.x, location.z);
    }
    return Block::air;    //This is for world edges
}

void Chunk_Blocks::addBlock(const Block_Location& location, int block)
{
    m_addedBlocks.insert(std::make_pair(location, block));
}


const std::unordered_map<Block_Location, int>& Chunk_Blocks::getAddedBlocks() const
{
    return m_addedBlocks;
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

void Chunk_Blocks::addLayers(unsigned target)
{
    while (m_layers.size() - 1 < target) m_layers.emplace_back();
}

size_t Chunk_Blocks::getLayerCount() const
{
    return m_layers.size();
}

int Chunk_Blocks::getMaxheightAt(int x, int z)
{
    return m_maxHeights[x * World::CHUNK_SIZE + z];
}

void Chunk_Blocks::setMaxHeight(const Block_Location& location)
{
    m_maxHeights[location.x * World::CHUNK_SIZE + location.z] = location.y;
}

