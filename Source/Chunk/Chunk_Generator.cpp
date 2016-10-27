#include "Chunk.h"

#include <iostream>
#include <string>

#include "Block/Block.h"
#include "Texture/Texture_Atlas.h"
#include "Loader.h"
#include "Random.h"
#include "Height_Generator.h"
#include "Block/D_Blocks.h"
#include "Chunk_Map.h"
#include "Debug_Display.h"



void Chunk :: generateBlockData()
{
    std::vector<int> m_heightMap;
    for (int x = 0; x < SIZE ; x ++)
    {
        for (int z = 0 ; z < SIZE ; z++)
        {
            m_heightMap.push_back (Height_Generator::getHeight
                                   (    x,
                                        z,
                                        m_location.x,
                                        m_location.z )
                                   );
        }
    }

    for (int y = 0; y < HEIGHT ; y++)
    {
        for (int x = 0 ; x < SIZE ; x++)
        {
            for (int z = 0 ; z < SIZE ; z++)
            {
                int h = m_heightMap.at ( x * SIZE + z );
                if (y > h)
                {
                    y <= WATER_LEVEL ?
                        qSetBlock( x, y, z, Block::water ) :
                        qSetBlock( x, y, z, Block::air );
                }
                else if ( y == h )
                {
                    if ( y > BEACH_LEVEL ) //Top levels
                    {
                        qSetBlock( x, y, z, Block::grass );
                        if ( Random::integer( 1, 90 ) == 1 )
                            m_treeLocations.emplace_back( x, y, z );    //Trees
                    }
                    else if ( y <= BEACH_LEVEL && y >= WATER_LEVEL) //Beach
                    {
                        qSetBlock( x, y, z, Block::sand );
                    }
                    else
                    {
                        Random::integer( 0, 10 ) < 6 ?
                            qSetBlock( x, y, z, Block::sand )   :
                            qSetBlock( x, y, z, Block::dirt );
                    }
                }
                else  if ( y < h && y > h - 5 )
                {
                    if ( y > WATER_LEVEL )
                        y <= BEACH_LEVEL ?
                            qSetBlock( x, y, z, Block::sand ) :
                            qSetBlock( x, y, z, Block::dirt );
                    else //Underwater
                    {
                        Random::integer( 0, 10 ) < 6 ?
                            qSetBlock( x, y, z, Block::sand ) :
                            qSetBlock( x, y, z, Block::dirt );
                    }
                }
                else
                {
                    qSetBlock( x, y, z, Block::stone );
                }
            }
        }
    }
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
    m_p_chunkMap->addChunk({m_location.x + 1, m_location.z});
    m_p_chunkMap->addChunk({m_location.x, m_location.z + 1});
    m_p_chunkMap->addChunk({m_location.x - 1, m_location.z});
    m_p_chunkMap->addChunk({m_location.x, m_location.z - 1});

    m_mesh.generateMesh();

    m_hasMesh       = true;
    m_hasBuffered   = false;
}

void Chunk :: bufferMesh ()
{
    m_mesh.bufferMesh();

    m_hasBuffered = true;
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
        qSetBlock( x, y + i, z, Block::oakWood, false );
    }
    for ( unsigned yLeaf = y + trunkHeight ; yLeaf < y + trunkHeight + 4 ; yLeaf++ )
    {
        for ( unsigned xLeaf = x - 2 ; xLeaf < x + 3 ; xLeaf++ )
        {
            for ( unsigned zLeaf = z - 2 ; zLeaf < z + 3 ; zLeaf++ )
            {
                qSetBlock( xLeaf, yLeaf, zLeaf, Block::oakLeaf, false );
            }
        }
    }
}
