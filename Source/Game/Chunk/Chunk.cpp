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

Chunk :: Chunk ( std::unordered_map<Vector2i, Chunk_Ptr>* chunkMap,
                 const Vector2i& location,
                 const Texture_Atlas& atlas  )
:   m_p_chunkMap    ( chunkMap )
,   m_blocks        ( WIDTH * WIDTH * HEIGHT )
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
                if ( y > h )
                {
                    if ( y <= WATER_LEVEL)
                        setBlock( x, y, z, water );
                    else
                        setBlock( x, y, z, air );
                }
                else if ( y == h )
                {
                    if ( y > BEACH_LEVEL ) //Top levels
                    {
                        setBlock( x, y, z, grass );
                        if ( Random::integer( 1, 10) == 10 )
                        {
                            makeTree( x, y, z );
                        }
                    }
                    else if ( y <= BEACH_LEVEL && y >= WATER_LEVEL) //Beach
                    {
                        setBlock( x, y, z, sand );
                    }
                    else
                    {
                        if ( Random::integer( 0, 10 ) < 6 )
                            setBlock( x, y, z, sand );
                        else
                            setBlock( x, y, z, dirt );
                    }
                }
                else  if ( y < h && y > h - 5 )
                {
                    if ( y > WATER_LEVEL )
                        setBlock( x, y, z, dirt );
                    else //Underwater
                    {
                        if ( Random::integer( 0, 10 ) < 6 )
                            setBlock( x, y, z, sand );
                        else
                            setBlock( x, y, z, dirt );
                    }
                }
                else
                {
                    setBlock( x, y, z, stone );
                }
            }
        }
    }
    m_hasBlockData = true;
    m_position = { location.x * WIDTH, location.z * WIDTH };
}

void Chunk :: setBlock (   GLuint x, GLuint y, GLuint z, Block_t& block )
{
    try
    {

        m_blocks.at( WIDTH * WIDTH * y + WIDTH * x + z ) = &block;
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
        return dirt;
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

const Vector2i& Chunk :: getLocation () const
{
    return m_location;
}

const Vector2& Chunk :: getPosition () const
{
    return m_position;
}
