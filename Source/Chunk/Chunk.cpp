#include "Chunk.h"

#include <iostream>
#include <stdexcept>
#include <thread>

#include "Blocks/Blocks.h"

#include "Utilities/Random.h"
#include "SimplexNoise.h"



namespace
{
    Block           air ( Block_Type::Air );

    Grass_Block     grass;
    Dirt_Block      dirt;
    Stone_Block     stone;

    SimplexNoise noise ( 0.5, 0.1, 0.2, 0.5 );
}

Chunk :: Chunk( Loader& loader, int x, int z )
:   m_xPos ( x )
,   m_zPos ( z )
{
    std::vector<int> heightMap;

    //Generate the height map
    for ( int heightMapX = 0 ; heightMapX < WIDTH; heightMapX++ ) {
        for ( int heightMapZ = 0 ; heightMapZ < WIDTH; heightMapZ++ ) {

            heightMap.push_back ( Height_Generator::getHeight( heightMapX,
                                                               heightMapZ,
                                                               m_xPos,
                                                               m_zPos ) );
        }
    }

    //Create blocks based on the height map
    for ( int y = 0 ; y < HEIGHT ; y++ ) {
        for ( int x = 0 ; x < WIDTH; x++ ) {
            for ( int z = 0 ; z < WIDTH; z++ ) {
                int h = heightMap.at( x * (WIDTH) + z );

                if ( y > h ) {
                    m_blocks.emplace_back( &air );
                }
                else if ( y == h ) {
                    m_blocks.emplace_back ( &grass );
                }
                else  if ( y < h && y > h - 5 ){
                    m_blocks.emplace_back ( &dirt );
                } else {
                    m_blocks.emplace_back( &stone );
                }
            }
        }
    }

    //Create the mesh for the blokcs
    for ( int y = 0 ; y < HEIGHT ; y++ ) {
        for ( int x = 0 ; x < WIDTH; x++ ) {
            for ( int z = 0 ; z < WIDTH; z++ ) {
                Block* b = &getBlock( x, y, z );
                if ( b->type == Block_Type::Air ) {
                    continue;
                } else {
                   makeBlock( x, y, z, *b );
                }
            }
        }
    }

    tempMesh = loader.loadToVAO( m_vertexList, m_textureList );
    tempMesh->pos = { x * WIDTH, 0, z * WIDTH };

    m_vertexList.clear();
    m_textureList.clear();
}

void Chunk :: reset( Loader& loader )
{
   std::vector<int> heightMap;

    //Create the mesh for the blokcs
    for ( int y = 0 ; y < HEIGHT ; y++ ) {
        for ( int x = 0 ; x < WIDTH; x++ ) {
            for ( int z = 0 ; z < WIDTH; z++ ) {
                Block* b = &getBlock( x, y, z );
                if ( b->type == Block_Type::Air ) {
                    continue;
                } else {
                   makeBlock( x, y, z, *b );
                }
            }
        }
    }

    tempMesh = loader.loadToVAO( m_vertexList, m_textureList );
    tempMesh->pos = { m_xPos * WIDTH, 0, m_zPos * WIDTH };

    m_vertexList.clear();
    m_textureList.clear();
}

Block& Chunk :: getBlock ( int x, int y, int z )
{
    static int area = ( WIDTH ) * ( WIDTH );
    try  {

        return *m_blocks.at ( area * y + ( WIDTH ) * x + z );
    } catch ( std::out_of_range& e ) {
        return air;
    }
}

Chunk::~Chunk()
{
    while ( !m_blocks.empty() ) {
        //delete m_blocks.back();
        m_blocks.pop_back();
    }
}
