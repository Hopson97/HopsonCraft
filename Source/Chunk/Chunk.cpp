#include "Chunk.h"

#include <iostream>
#include <stdexcept>
#include <thread>

#include "Blocks/Blocks.h"

#include "Utilities/Random.h"

Block Chunk :: air ( Block_Type::Air );

Chunk :: Chunk( Loader& loader, int x, int z, Height_Generator& generator )
    :   m_xPos ( x )
    ,   m_zPos ( z )
{
    std::vector<int> heightMap ( WIDTH * WIDTH );

    //Generate the height map
    for ( int x = 0 ; x < WIDTH ; x++ ) {
        for ( int z = 0 ; z < WIDTH ; z++ ) {
            heightMap[ z * WIDTH + x ] = generator.generateHeight( x * m_xPos, z * m_zPos );
        }
    }

    //Create blocks based on the height map
    for ( int y = 0 ; y < HEIGHT ; y++ ) {
        for ( int z = 0 ; z < WIDTH ; z++ ) {
            for ( int x = 0 ; x < WIDTH ; x++ ) {
                int h = heightMap.at( z * WIDTH + x );

                if ( y > h ) {
                    m_blocks.emplace_back( &air );
                }
                else if ( y == h ) {
                    m_blocks.emplace_back ( new Grass_Block () );
                }
                else  if ( y < h && y > h - 5 ){
                    m_blocks.emplace_back ( new Dirt_Block () );
                } else {
                    m_blocks.emplace_back( new Stone_Block() );
                }

                //m_blocks.emplace_back ( new Grass_Block () );
            }
        }
    }

    //Create the mesh for the blokcs
    for ( int y = 0 ; y < HEIGHT ; y++ ) {
        for ( int z = 0 ; z < WIDTH ; z++ ) {
            for ( int x = 0 ; x < WIDTH ; x++ ) {
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

Block& Chunk :: getBlock ( int x, int y, int z )
{
    static int area = WIDTH * WIDTH;
    try  {
        return *m_blocks.at ( area * y + WIDTH * z + x );
    } catch ( std::out_of_range& e ) {
        return air;
    }
}

Chunk::~Chunk()
{
    while ( !m_blocks.empty() ) {
        delete m_blocks.back();
        m_blocks.pop_back();
    }
}

