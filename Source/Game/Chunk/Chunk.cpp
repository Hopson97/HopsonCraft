#include "Chunk.h"

#include <iostream>

#include "Blocks.h"

#include "Loader.h"
#include "Height_Generator.h"

#include "Random.h"


int Chunk::maxHeight = 0;
int Chunk::minHeight = 0xFFF;

Chunk :: Chunk ( std::unordered_map<Vector2i, Chunk_Ptr>* chunkMap,
                 const Vector2i& location,
                 const Texture_Atlas& atlas  )
:   m_p_chunkMap    ( chunkMap )
,   m_blocks        ( WIDTH * WIDTH * HEIGHT )
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
                }

                if ( y > h )
                {
                    if ( y <= WATER_LEVEL)
                        setBlock( x, y, z, std::make_unique<Block::Water>() );
                    else
                        setBlock( x, y, z, std::make_unique<Block::Block_Base>( Block::ID::Air ) );
                }
                else if ( y == h )
                {
                    if ( y > BEACH_LEVEL ) //Top levels
                    {
                        setBlock( x, y, z, std::make_unique<Block::Grass>() );
                        if ( Random::integer( 1, 10) == 10 )
                        {
                            makeTree( x, y, z );
                        }
                    }
                    else //Beach
                    {
                        setBlock( x, y, z, std::make_unique<Block::Sand>() );
                    }
                }
                else  if ( y < h && y > h - 5 )
                {
                    if ( y > WATER_LEVEL )
                        setBlock( x, y, z, std::make_unique<Block::Dirt>() );
                    else //Underwater
                    {
                        if ( Random::integer( 0, 10 ) < 7 )
                            setBlock( x, y, z, std::make_unique<Block::Sand>() );
                        else
                            setBlock( x, y, z, std::make_unique<Block::Dirt>() );
                    }
                }
                else
                {
                    setBlock( x, y, z, std::make_unique<Block::Stone>() );
                }
            }
        }
    }
    m_hasBlockData = true;
    m_position = { location.x * WIDTH, location.z * WIDTH };
}

void Chunk :: setBlock (   GLuint x, GLuint y, GLuint z, std::unique_ptr<Block::Block_Base> block )
{
    try
    {

        m_blocks.at( WIDTH * WIDTH * y + WIDTH * x + z ) = std::move( block );
    }
    catch ( std::out_of_range& e )
    {
        return;
    }
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

const Vector2& Chunk :: getPosition () const
{
    return m_position;
}
