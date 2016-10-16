#include "Chunk.h"

#include <iostream>

#include "Blocks.h"

#include "Loader.h"
#include "Height_Generator.h"

#include "Random.h"



namespace
{
    Block_t         air     ( Block::ID::Air );
    Block::Grass    grass;
    Block::Dirt     dirt;
    Block::Stone    stone;
    Block::Water    water;
    Block::Sand     sand;
    Block::Oak_Wood oakWood;
    Block::Oak_Leaf oakLeaf;
}

Chunk :: Chunk ( std::unordered_map<Vector2i, Chunk_Ptr>& chunkMap,
                 const Vector2i& location,
                 const Texture_Atlas& atlas  )
:   m_p_chunkMap    ( &chunkMap )
,   m_blocks        ( WIDTH * WIDTH * HEIGHT )
,   m_location      ( location )
,   m_p_atlas       ( &atlas )
{
    m_position = { location.x * WIDTH, location.z * WIDTH };
    generateBlockData();
    tempBool = true;
}

void Chunk :: setBlock (   GLuint x, GLuint y, GLuint z, Block::ID id, bool overrideBlocks )
{
    switch ( id )
    {
        case Block::ID::Air:
            return;
        case Block::ID::Dirt:
            setBlock( x, y, z, dirt, overrideBlocks );
            break;

        case Block::ID::Grass:
            setBlock( x, y, z, grass, overrideBlocks );
            break;

        case Block::ID::Stone:
            setBlock( x, y, z, stone, overrideBlocks );
            break;

        case Block::ID::Oak_Leaf:
            setBlock( x, y, z, oakLeaf, overrideBlocks );
            break;

        case Block::ID::Oak_Wood:
            setBlock( x, y, z, oakWood, overrideBlocks );
            break;

        case Block::ID::Sand:
            setBlock( x, y, z, sand, overrideBlocks );
            break;

        case Block::ID::Water:
            setBlock( x, y, z, water, overrideBlocks );
            break;
        case Block::ID::NUM_BLOCK_TYPES:
            return;
    }

    m_hasVertexData     = false;
    m_hasBufferedData   = false;
}

void Chunk :: setBlock (   GLuint x, GLuint y, GLuint z, Block_t& block, bool overrideBlocks )
{
    if ( y > HEIGHT - 1 || y < 0 ) return;
    if ( x < 0 )
    {
        if ( m_p_chunkMap->find( { m_location.x - 1, m_location.z } ) != m_p_chunkMap->end() )
        {
            m_p_chunkMap->at( { m_location.x - 1, m_location.z } )->setBlock ( WIDTH + x, y, z, block, overrideBlocks );
        }
    }
    else if ( z < 0 )
    {
        if ( m_p_chunkMap->find( { m_location.x, m_location.z - 1 } ) != m_p_chunkMap->end() )
        {
            m_p_chunkMap->at( { m_location.x, m_location.z - 1 } )->setBlock ( x, y, WIDTH + z, block, overrideBlocks );
        }
    }
    else if ( x >= WIDTH )
    {
        if ( m_p_chunkMap->find( { m_location.x + 1, m_location.z } ) != m_p_chunkMap->end() )
        {
            int diff = x - WIDTH;
            m_p_chunkMap->at( { m_location.x + 1, m_location.z } )->setBlock ( WIDTH + diff, y, z, block, overrideBlocks );
        }
        else
        {

        }
    }
    else if ( z >= WIDTH )
    {
        if ( m_p_chunkMap->find( { m_location.x, m_location.z + 1 } ) != m_p_chunkMap->end() )
        {
            int diff = z - WIDTH;
            m_p_chunkMap->at( { m_location.x, m_location.z + 1 } )->setBlock ( x, y, diff + WIDTH, block, overrideBlocks );
        }
    }
    else
    {
        if ( !m_blocks.at( WIDTH * WIDTH * y + WIDTH * x + z ) )
        {
            m_blocks.at( WIDTH * WIDTH * y + WIDTH * x + z ) = &block;
            return;
        }
        else if ( getBlock( x, y, z).getID() == Block::ID::Air )
        {
            m_blocks.at( WIDTH * WIDTH * y + WIDTH * x + z ) = &block;
            return;
        }
        else if ( overrideBlocks )
        {
            m_blocks.at( WIDTH * WIDTH * y + WIDTH * x + z ) = &block;
            return;
        }
    }
}

const Block_t& Chunk :: getBlock ( int x, int y, int z ) const
{
    if ( x == -1 )
    {
        if ( m_p_chunkMap->find( { m_location.x - 1, m_location.z } ) != m_p_chunkMap->end() )
        {
            return m_p_chunkMap->at( { m_location.x - 1, m_location.z } )->getBlock ( WIDTH - 1, y, z );
        }
    }
    else if ( z == -1 )
    {
        if ( m_p_chunkMap->find( { m_location.x, m_location.z - 1 } ) != m_p_chunkMap->end() )
        {

            return m_p_chunkMap->at( { m_location.x, m_location.z - 1 } )->getBlock ( x, y, WIDTH - 1 );
        }
    }
    else if ( x == WIDTH )
    {
        if ( m_p_chunkMap->find( { m_location.x + 1, m_location.z } ) != m_p_chunkMap->end() )
        {
            return m_p_chunkMap->at( { m_location.x + 1, m_location.z } )->getBlock ( 0, y, z );
        }
    }
    else if ( z == WIDTH )
    {
        if ( m_p_chunkMap->find( { m_location.x, m_location.z + 1 } ) != m_p_chunkMap->end() )
        {
            return m_p_chunkMap->at( { m_location.x, m_location.z + 1 } )->getBlock ( x, y, 0 );
        }
    }
    else if ( y == -1 || y > HEIGHT - 1 )
    {
        return dirt;
    }
    else
    {
        return *m_blocks.at( WIDTH * WIDTH * y + WIDTH * x + z );
    }
    return dirt;    //This is for world edges.
}

const Block_t& Chunk :: getBlock ( const Vector3& location ) const
{
    return getBlock( location.x, location.y, location.z );
}

const AABB Chunk :: getBlockAABBTop ( const Vector3& location ) const
{
    int x = location.x;
    int y = location.y;
    int z = location.z; //Cast to int

    if ( getBlock( x, y, z ).getID() == Block::ID::Air ) return Vector3{ 0, 0, 0 };

    AABB block ( { 1, 1, 1 } );
    block.setPosition( { x, y + 1, z } );
    return block;
}

bool Chunk :: hasVertexData () const
{
    return m_hasVertexData;
}

bool Chunk :: hasBlockData   () const
{
    return m_hasBlockData;
}

bool Chunk :: hasBuffered () const
{
    return m_hasBufferedData;
}


const Vector2i& Chunk :: getLocation () const
{
    return m_location;
}

const Vector2& Chunk :: getPosition () const
{
    return m_position;
}

const Model& Chunk :: getChunkModel  () const
{
    return m_solidPart.model;
}
const Model& Chunk :: getWaterModel  () const
{
    return m_waterPart.model;
}
const Model& Chunk :: getFloraModel  () const
{
    return m_solidPart.model;
}





