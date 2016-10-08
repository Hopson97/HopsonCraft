#include "Chunk.h"

#include <iostream>

#include "Blocks.h"

#include "Loader.h"
#include "Height_Generator.h"


int Chunk::maxHeight = 0;
int Chunk::minHeight = 0xFFF;

Chunk :: Chunk ( std::unordered_map<Vector2i, Chunk_Ptr>* chunkMap,
                 const Vector2i& location,
                 const Texture_Atlas& atlas  )
:   m_p_chunkMap    ( chunkMap )
,   m_location      ( location )
,   m_p_atlas       ( &atlas )
,   m_dirtBlock     ( std::make_unique<Block::Dirt>() )
,   m_airBlock      ( std::make_unique<Block::Block_Base> ( Block::ID::Air ) )
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
                    m_blocks.emplace_back( std::make_unique<Block::Block_Base>( Block::ID::Air ) );
                }
                else if ( y == h )
                {
                    m_blocks.emplace_back ( std::make_unique<Block::Grass>() );
                }
                else  if ( y < h && y > h - 5 )
                {
                    m_blocks.emplace_back ( std::make_unique<Block::Dirt>() );
                }
                else
                {
                    m_blocks.emplace_back ( std::make_unique<Block::Stone>() );
                }
            }
        }
    }
    m_hasBlockData = true;
    position = { location.x * WIDTH, 0, location.z* WIDTH };
}

Chunk :: ~Chunk()
{
    while ( !m_blocks.empty() )
    {
        m_blocks.erase( m_blocks.begin() );
    }
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
    else if ( y == -1 )
    {
        return *m_dirtBlock;
    }
    else
    {
        return *m_blocks.at( WIDTH * WIDTH * y + WIDTH * x + z );
    }
    return *m_airBlock;
}

bool Chunk :: hasVertexData () const
{
    return m_hasVertexData;
}

const Vector2i& Chunk :: getLocation () const
{
    return m_location;
}
