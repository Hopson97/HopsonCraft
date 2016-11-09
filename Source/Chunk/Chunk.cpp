#include "Chunk.h"

#include <iostream>
#include <fstream>

#include "Block/Block.h"
#include "Loader.h"
#include "Random.h"
#include "Block/D_Blocks.h"
#include "Chunk_Map.h"
#include "Function_Toggle_Key.h"
#include "Noise_Generator.h"

Chunk::Chunk(const Chunk_Location& position, Chunk_Map& chunkMap, const Texture_Atlas& blockAtlas)
//:   m_layers        (WATER_LEVEL + 1)
:   m_location      (position)
,   m_position      (position.x * SIZE, position.z * SIZE)
,   m_p_chunkMap    (&chunkMap)
,   m_p_atlas       (&blockAtlas)
,   m_mesh          (*this)
,   m_blocks        (*this, m_location, *m_p_chunkMap)
{
    generateBlockData ();
    generateStructureData ();
    loadBlockData ();

    m_hasBlockData = true;
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
    if(!m_blocks.getAddedBlocks().empty())
    {
        std::ofstream outFile (getFileString());

        for(auto& block : m_blocks.getAddedBlocks())
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

Chunk_Blocks& Chunk::getBlocks()
{
    return m_blocks;
}

const Chunk_Blocks& Chunk::getBlocks() const
{
    return m_blocks;
}
