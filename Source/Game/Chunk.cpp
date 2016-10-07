#include "Chunk.h"

#include <iostream>

#include "Blocks.h"

#include "Loader.h"

namespace
{
    Block::Block_Base   air     ( false );
    Block::Grass        grass;
    Block::Dirt         dirt;
}

Chunk :: Chunk( int x, int z,
                const Texture_Atlas& atlas )
:   m_p_atlas       ( &atlas )
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

    position = { x, 0, z };
}

void Chunk :: generateMesh ()
{
    for ( int y = 0; y < HEIGHT ; y++ )
    {
        for ( int x = 0 ; x < WIDTH ; x++ )
        {
            for ( int z = 0 ; z < WIDTH ; z++ )
            {

                if ( !getBlock( x, y, z ).isOpaque() )
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
        return *m_blocks.at( WIDTH * WIDTH * y + WIDTH * x + z );
    }
    catch ( std::out_of_range& e )
    {
        return air;
    }
}
