#include "Chunk.h"

#include <iostream>
#include <fstream>
#include <windows.h>

#include "Block/Block.h"

#include "Loader.h"
#include "Height_Generator.h"

#include "Random.h"
#include "Block/D_Blocks.h"
#include "Chunk_Map.h"
#include "Function_Toggle_Key.h"
#include "Noise_Generator.h"

Chunk::Chunk(const Chunk_Location& position, Chunk_Map& chunkMap, const Texture_Atlas& blockAtlas)
:   m_layers        (WATER_LEVEL + 1)
,   m_location      (position)
,   m_position      (position.x * SIZE, position.z * SIZE)
,   m_p_chunkMap    (&chunkMap)
,   m_p_atlas       (&blockAtlas)
,   m_mesh          (*this)
{
    generateBlockData ();
    generateStructureData ();
    loadBlockData ();

    m_hasBlockData = true;
}

void Chunk :: setBlock (const Block_Location& location, Block::Block_Base& block, bool overrideBlocks)
{
    //if ( position.x < 0 )
    {
       // m_p_chunkMap->addChunk({-1, m_location.z});
        //m_p_chunkMap->getChunkAt({-1, m_location.z})->setBlock(SIZE - x, y, z);
    }
    //else if ( position.z < 0 )
    {

    }
    //else if ( position.x >= SIZE )
    {

    }
    //else if ( position.z >= SIZE )
    {


    }
    //else
    {
        qSetBlock(location, block, overrideBlocks);
    }
}

void Chunk::qSetBlock (const Block_Location& location, Block_t& block, bool overrideBlocks)
{
    if ((unsigned)location.y > m_layers.size() - 1)
    {
        addLayers(location.y);
    }

    if (m_layers.at(location.y).getBlock(location.x, location.z).getID() == Block::ID::Air || overrideBlocks)
    {
        if (m_hasBlockData)
        {
            m_addedBlocks[location] = static_cast<int>(block.getID());
        }
        m_layers.at(location.y).setBlock(location.x, location.z, block);
    }
}

void Chunk::addLayers (unsigned target)
{
    while (m_layers.size() - 1 < target) m_layers.emplace_back();
}

const Block_t& Chunk::getBlock (const Block_Location& location) const
{
    //Check if trying to get a block from other chunk
    if (location.x == -1 )
    {
        return getAdjChunkBlock(-1, 0, {SIZE - 1, location.y, location.z});
    }
    else if (location.z == -1 )
    {
        return getAdjChunkBlock(0, -1, {location.x, location.y, SIZE - 1});
    }
    else if (location.x == SIZE )
    {
        return getAdjChunkBlock(1, 0, {0, location.y, location.z});
    }
    else if (location.z == SIZE )
    {
        return getAdjChunkBlock(0, 1, {location.z, location.y, 0});
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

const Block_t& Chunk::getAdjChunkBlock (int xChange, int zChange, const Block_Location& location) const
{
    //Try dd a chunk incase it does not yet exist
    Chunk_Location chunkLocation ( m_location.x + xChange, m_location.z + zChange);
    m_p_chunkMap->addChunk(chunkLocation);

    //Return the respective block...
    return m_p_chunkMap->getChunkAt(chunkLocation)->getBlock(location);
}

bool Chunk::hasMesh () const
{
    return m_hasMesh;
}


bool Chunk::hasBlockData () const
{
    return m_hasBlockData;
}


bool Chunk::hasBuffered () const
{
    return m_hasBuffered;
}


const Chunk_Location& Chunk::getLocation () const
{
    return m_location;
}


const Vector2& Chunk::getPosition () const
{
    return m_position;
}

const Model& Chunk::getChunkModel  () const
{
    return m_mesh.getSolidPart().model;
}


const Model& Chunk::getWaterModel  () const
{
    return m_mesh.getWaterPart().model;
}


void Chunk::giveDeleteFlag ()
{
    saveToFile();
    m_hasDeleteFlag = true;
}

void Chunk::saveToFile()
{
    if(!m_addedBlocks.empty())
    {
        std::ofstream outFile (getFileString());

        for(auto& block : m_addedBlocks)
        {
            const Block_Location& l = block.first;

            outFile << l.x << " " << l.y << " " << l.z << " ";
            outFile << block.second << std::endl;
        }
    }
}


bool Chunk::hasDeleteFlag () const
{
    return m_hasDeleteFlag;
}

const Texture_Atlas& Chunk::getAtlas() const
{
    return *m_p_atlas;
}

void Chunk::update()
{
    generateMesh();
    bufferMesh();
    m_hasUpdateFlag = false;
}

void Chunk::giveUpdateFlag()
{
    m_hasUpdateFlag = true;
}

bool Chunk::hasUpdateFlag() const
{
    return m_hasUpdateFlag;
}

std::string Chunk::getFileString()
{
    return "Worlds/" +
            std::to_string(Noise_Generator::getSeed()) +
            "/" +
            std::to_string(m_location.x)
            + " "
            + std::to_string(m_location.z);
}

