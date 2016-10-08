#include "Chunk.h"

#include <iostream>

#include "Blocks.h"

#include "Loader.h"
#include "Height_Generator.h"

namespace
{
Block::Block_Base   air     ( Block::ID::Air );
Block::Grass        grass;
Block::Dirt         dirt;
Block::Stone        stone;
}

int Chunk::maxHeight = 0;
int Chunk::minHeight = 0xFFF;

Chunk :: Chunk ( std::unordered_map<Vector2i, Chunk_Ptr>* chunkMap,
                 const Vector2i& location,
                 const Texture_Atlas& atlas  )
    :   m_p_chunkMap    ( chunkMap )
    ,   m_location      ( location )
    ,   m_p_atlas       ( &atlas )
{
    std::vector<int> m_heightMap;
    for ( int x = 0; x < WIDTH ; x ++ )
    {
        for ( int z = 0 ; z < WIDTH ; z++ )
        {
            m_heightMap.push_back ( Height_Generator::getHeight ( x,
                                    z,
                                    location.x,
                                    location.z ) );
        }
    }

    for ( int y = 0; y < HEIGHT ; y++ )
    {
        for ( int x = 0 ; x < WIDTH ; x++ )
        {
            for ( int z = 0 ; z < WIDTH ; z++ )
            {
                int h = m_heightMap.at ( x * WIDTH + z );
                if ( h > maxHeight )
                {
                    maxHeight = h;
                }
                if ( h < minHeight )
                {
                    minHeight = h;
                    std::cout << h << std::endl;
                }

                if ( y > h )
                {
                    m_blocks.emplace_back( &air );
                }
                else if ( y == h )
                {
                    m_blocks.emplace_back ( &grass );
                }
                else  if ( y < h && y > h - 5 )
                {
                    m_blocks.emplace_back ( &dirt );
                }
                else
                {
                    m_blocks.emplace_back( &stone );
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
{/*
    try
    {
        return *m_blocks.at( WIDTH * WIDTH * y + WIDTH * x + z );
    }
    catch ( std::out_of_range& e )
    {
        return air;
    }*/
    if ( x == -1 )
    {
        if ( m_p_chunkMap->find( { m_location.x - 1, m_location.z } ) != m_p_chunkMap->end() )
        {
            assert( m_p_chunkMap->at( { m_location.x - 1, m_location.z } )->m_location.x == m_location.x - 1);
            return m_p_chunkMap->at( { m_location.x - 1, m_location.z } )->getBlock ( WIDTH - 1, y, z );
        }
    }
    else if ( z == -1 )
    {
        if ( m_p_chunkMap->find( { m_location.x, m_location.z - 1 } ) != m_p_chunkMap->end() )
        {
            assert( m_p_chunkMap->at( { m_location.x, m_location.z - 1 } )->m_location.z == m_location.z - 1);
            return m_p_chunkMap->at( { m_location.x, m_location.z - 1 } )->getBlock ( x, y, WIDTH - 1 );
        }
    }
    else if ( x == WIDTH )
    {
        if ( m_p_chunkMap->find( { m_location.x + 1, m_location.z } ) != m_p_chunkMap->end() )
        {
            assert( m_p_chunkMap->at( { m_location.x + 1, m_location.z } )->m_location.x == m_location.x + 1);
            return m_p_chunkMap->at( { m_location.x + 1, m_location.z } )->getBlock ( 0, y, z );
        }
    }
    else if ( z == WIDTH )
    {
        if ( m_p_chunkMap->find( { m_location.x, m_location.z + 1 } ) != m_p_chunkMap->end() )
        {
            assert( m_p_chunkMap->at( { m_location.x, m_location.z + 1 } )->m_location.z == m_location.z + 1);
            return m_p_chunkMap->at( { m_location.x, m_location.z + 1 } )->getBlock ( x, y, 0 );
        }
    }
    else if ( y == -1 )
    {
        return air;
    }
    else
    {
        return *m_blocks.at( WIDTH * WIDTH * y + WIDTH * x + z );
    }
    return air;
}

bool Chunk :: hasVertexData () const
{
    return m_hasVertexData;
}
