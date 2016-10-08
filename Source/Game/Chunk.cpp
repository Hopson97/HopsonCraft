#include "Chunk.h"

#include <iostream>

#include "Blocks.h"

#include "Loader.h"

namespace
{
    Block::Block_Base   air     ( false, Block::ID::Air );
    Block::Grass        grass;
    Block::Dirt         dirt;
}

Chunk :: Chunk ( std::unordered_map<Vector2i, Chunk_Ptr>* chunkMap,
                 const Vector2i& location,
                 const Texture_Atlas& atlas  )
:   m_p_chunkMap    ( chunkMap )
,   m_location      ( location )
,   m_p_atlas       ( &atlas )
{
    for ( int y = 0; y < HEIGHT ; y++ )
    {
        for ( int x = 0 ; x < WIDTH ; x++ )
        {
            for ( int z = 0 ; z < WIDTH ; z++ )
            {
                if ( y == HEIGHT - 1 )
                {
                    m_blocks.push_back( &grass );
                }
                else
                {
                    m_blocks.push_back ( &dirt );
                }
            }
        }
    }
    m_hasBlockData = true;
    position = { location.x * WIDTH, 0, location.z* WIDTH };
}

void Chunk :: generateMesh ()
{
    for ( int y = 0; y < HEIGHT ; y++ )
    {
        for ( int x = 0 ; x < WIDTH ; x++ )
        {
            for ( int z = 0 ; z < WIDTH ; z++ )
            {

                if ( getBlock( x, y, z ).getID() == Block::ID::Air )
                {
                    continue;
                }
                makeBlock( x, y, z, getBlock( x, y, z ) );
            }
        }
    }
    m_model.addData ( Loader::loadArrayMesh( m_vertexCoords, m_textureCoords ) );
    m_vertexCoords.clear();
    m_textureCoords.clear();

    m_hasVertexData = true;
}

const Model& Chunk :: getModel () const
{
    return m_model;
}

const Block :: Block_Base&
Chunk :: getBlock ( int x, int y, int z ) const
{

    try
    {
        if ( x == -1 )
        {
            if ( m_p_chunkMap->find( { m_location.x - 1, m_location.z } ) != m_p_chunkMap->end() )
                return m_p_chunkMap->at( { m_location.x - 1, m_location.z } )->getBlock ( WIDTH - 1, y, z );
        }
        else if ( z == -1 )
        {
            if ( m_p_chunkMap->find( { m_location.x, m_location.z - 1 } ) != m_p_chunkMap->end() )
                return m_p_chunkMap->at( { m_location.x, m_location.z - 1 } )->getBlock ( x, y, WIDTH - 1 );
        }
        else if ( x == WIDTH )
        {
            if ( m_p_chunkMap->find( { m_location.x + 1, m_location.z } ) != m_p_chunkMap->end() )
                return m_p_chunkMap->at( { m_location.x + 1, m_location.z } )->getBlock ( 0, y, z );
        }
        else if ( z == WIDTH )
        {
            if ( m_p_chunkMap->find( { m_location.x, m_location.z + 1 } ) != m_p_chunkMap->end() )
                return m_p_chunkMap->at( { m_location.x, m_location.z + 1 } )->getBlock ( x, y, 0 );
        }
        else
        {
            return *m_blocks.at( WIDTH * WIDTH * y + WIDTH * x + z );
        }
    }
    catch ( std::out_of_range& e )
    {
        return air;
    }
    return air;
}
