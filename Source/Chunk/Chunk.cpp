#include "Chunk.h"

#include <iostream>

#include "Block/Block.h"

#include "Loader.h"
#include "Height_Generator.h"

#include "Random.h"
#include "Block/D_Blocks.h"
#include "Chunk_Map.h"

Chunk::Chunk(const Chunk_Location& position, Chunk_Map& chunkMap, const Texture_Atlas& blockAtlas)
:   m_blocks        ( SIZE * SIZE * HEIGHT )
,   m_location      (position)
,   m_position      (position.x * SIZE, position.z * SIZE)
,   m_p_chunkMap    (&chunkMap)
,   m_p_atlas       (&blockAtlas)
,   m_mesh          (*this)
{
    generateBlockData       ();
    generateStructureData   ();
}

void Chunk :: setBlock (const Vector3& position, Block::Block_Base& block, bool overrideBlocks)
{
    if (position.y > HEIGHT - 1 || position.y < 0) return;
/*
    if ( position.x < 0 )
    {

    }
    else if ( position.z < 0 )
    {

    }
    else if ( position.x >= SIZE )
    {

    }
    else if ( position.z >= SIZE )
    {


    }
    else
    {*/
        qSetBlock(position.x, position.y, position.z, block, overrideBlocks);
    //}
}

void Chunk::qSetBlock (GLuint x, GLuint y, GLuint z, Block_t& block, bool overrideBlocks)
{
    if (!m_blocks.at(SIZE * SIZE * y + SIZE * x + z))
    {
        m_blocks.at(SIZE * SIZE * y + SIZE * x + z) = &block;
    }
    else if ( getBlock(x, y, z).getID() == Block::ID::Air)
    {
        m_blocks.at(SIZE * SIZE * y + SIZE * x + z) = &block;
    }
    else if (overrideBlocks)
    {
        m_blocks.at(SIZE * SIZE * y + SIZE * x + z) = &block;
    }
}

const Block_t& Chunk::getBlock (int x, int y, int z) const
{
    //Check if trying to get a block from other chuky
    if (x == -1 )
    {
        return getAdjChunkBlock(-1, 0, SIZE - 1, y, z);
    }
    else if (z == -1 )
    {
        return getAdjChunkBlock(0, -1, x, y, SIZE - 1);
    }
    else if (x == SIZE )
    {
        return getAdjChunkBlock(1, 0, 0, y, z);
    }
    else if (z == SIZE )
    {
        return getAdjChunkBlock(0, 1, z, y, 0);
    }
    else if (y > HEIGHT - 1)
    {
        return Block::air;
    }
    else if (y < 0)
    {
        return Block::dirt;
    }
    else
    {
        return *m_blocks.at(SIZE * SIZE * y + SIZE * x + z);
    }
    return Block::dirt;    //This is for world edges
}

const Block_t& Chunk::getBlock(const Vector3& location) const
{
    return getBlock(location.x, location.y, location.z);
}




const Block_t& Chunk::getAdjChunkBlock ( int xChange, int zChange, int blockX, int blockY, int blockZ ) const
{
    Chunk_Location location ( m_location.x + xChange, m_location.z + zChange);
    m_p_chunkMap->addChunk(location);
    return m_p_chunkMap->getChunkAt(location)->getBlock(blockX, blockY, blockZ);
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


void Chunk::setToDelete ()
{
    m_hasDeleteFlag = true;
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


