#include "Chunk.h"

#include <iostream>

#include "Block.h"
#include "Texture_Atlas.h"
#include "Loader.h"
#include "Blocks.h"
#include "Random.h"
#include "Height_Generator.h"

namespace
{
    Block_t         air;
    Block::Grass    grass;
    Block::Dirt     dirt;
    Block::Stone    stone;
    Block::Water    water;
    Block::Sand     sand;
    Block::Oak_Wood oakWood;
    Block::Oak_Leaf oakLeaf;
}

void Chunk :: generateBlockData()
{
    std::vector<int> m_heightMap;
    for ( int x = 0; x < WIDTH ; x ++ )
    {
        for ( int z = 0 ; z < WIDTH ; z++ )
        {
            m_heightMap.push_back ( Height_Generator::getHeight ( x,
                                    z,
                                    m_location.x,
                                    m_location.z ) );
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
                    y <= WATER_LEVEL ?
                        setBlock( x, y, z, water ) :
                        setBlock( x, y, z, air );
                }
                else if ( y == h )
                {
                    if ( y > BEACH_LEVEL ) //Top levels
                    {
                        setBlock( x, y, z, grass );
                        if ( Random::integer( 1, 90 ) == 1 )
                            m_treeLocations.emplace_back( x, y, z );    //Trees
                    }
                    else if ( y <= BEACH_LEVEL && y >= WATER_LEVEL) //Beach
                    {
                        setBlock( x, y, z, sand );
                    }
                    else
                    {
                        Random::integer( 0, 10 ) < 6 ?
                            setBlock( x, y, z, sand )   :
                            setBlock( x, y, z, dirt );
                    }
                }
                else  if ( y < h && y > h - 5 )
                {
                    if ( y > WATER_LEVEL )
                        y <= BEACH_LEVEL ?
                            setBlock( x, y, z, sand ) :
                            setBlock( x, y, z, dirt );
                    else //Underwater
                    {
                        Random::integer( 0, 10 ) < 6 ?
                            setBlock( x, y, z, sand ) :
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
    //temp
    m_hasBlockData = true;
}

void Chunk :: generateStructureData ()
{
    for ( auto& loc : m_treeLocations )
    {
        makeTree( loc.x, loc.y, loc.z );
    }
    m_treeLocations.clear();

    m_hasBlockData = true;
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
    m_hasVertexData     = true;
    m_hasBufferedData   = false;
}

void Chunk :: bufferMesh ()
{
    m_solidPart.buffer();
    m_waterPart.buffer();

    m_hasBufferedData = true;
}

void Chunk :: Chunk_Part :: buffer ()
{
    model.addData ( Loader::loadArrayMesh( vertexData, textureData ) );
    vertexData.clear();
    textureData.clear();
}

void Chunk :: makeTree   (   GLuint x, GLuint y, GLuint z )
{
    unsigned trunkHeight = Random::integer( 5, 8 );
    for ( unsigned i = 1 ; i < trunkHeight + 1 ; i++ )
    {
        setBlock( x, y + i, z, oakWood, false );
    }
    for ( unsigned yLeaf = y + trunkHeight ; yLeaf < y + trunkHeight + 4 ; yLeaf++ )
    {
        for ( unsigned xLeaf = x - 2 ; xLeaf < x + 3 ; xLeaf++ )
        {
            for ( unsigned zLeaf = z - 2 ; zLeaf < z + 3 ; zLeaf++ )
            {
                setBlock( xLeaf, yLeaf, zLeaf, oakLeaf, false );
            }
        }
    }
}
