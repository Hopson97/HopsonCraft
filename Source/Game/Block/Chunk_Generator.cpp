#include "Chunk.h"

#include <iostream>

#include "Block.h"
#include "Texture_Atlas.h"
#include "Loader.h"
#include "Blocks.h"
#include "Random.h"

void Chunk :: makeTree   (   GLuint x, GLuint y, GLuint z )
{
    int trunkHeight = Random::integer( 4, 6 );
    for ( int i = 1 ; i < trunkHeight + 1 ; i++ )
    {
        setBlock( x, y + i, z, std::make_unique<Block::Oak_Wood>() );
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

void Chunk :: makeBlock ( GLfloat x, GLfloat y, GLfloat z, const Block::Block_Base& block )
{
    /**/
    if (  getBlock ( x, y + 1, z).getID() == Block::ID::Air ||
       ( !getBlock ( x, y + 1, z).isOpaque() && getBlock ( x, y + 1, z).getID() != block.getID() )  )
    {
        makeTop( x, y, z, block );
    }

    if (  getBlock ( x, y - 1, z).getID() == Block::ID::Air ||
       ( !getBlock ( x, y - 1, z).isOpaque() && getBlock ( x, y - 1, z).getID() != block.getID() )  )
    {
        makeBottom( x, y, z, block );
    }


    if (  getBlock ( x, y, z + 1).getID() == Block::ID::Air ||
       ( !getBlock ( x, y, z + 1).isOpaque() && getBlock ( x, y, z + 1).getID() != block.getID() )  )
    {
        makeFront( x, y, z, block );
    }

    if (  getBlock ( x, y, z - 1).getID() == Block::ID::Air ||
       ( !getBlock ( x, y, z - 1).isOpaque() && getBlock ( x, y, z - 1).getID() != block.getID() )  )
    {
        makeBack( x, y, z, block );
    }


    if (  getBlock ( x - 1, y, z).getID() == Block::ID::Air ||
       ( !getBlock ( x - 1, y, z).isOpaque() && getBlock ( x - 1, y, z).getID() != block.getID() )  )
    {
        makeLeft( x, y, z, block );
    }

    if (  getBlock ( x + 1, y, z).getID() == Block::ID::Air ||
       ( !getBlock ( x + 1, y, z).isOpaque() && getBlock ( x + 1, y, z).getID() != block.getID() )  )
    {
        makeRight( x, y, z, block );
    }
}

/*
 *  This marks the start of creating blocks
 */

void Chunk :: makeFront ( GLfloat x, GLfloat y, GLfloat z, const Block::Block_Base& block )
{
    std::vector<GLfloat> vertices =
    {
        x,      y,      z + 1,
        x + 1,  y,      z + 1,
        x + 1,  y + 1,  z + 1,
        x + 1,  y + 1,  z + 1,
        x,      y + 1,  z + 1,
        x,      y,      z + 1,
    };
    std::vector<GLfloat> textureCoords = m_p_atlas->getTextureCoords( block.getTextureSide() );

    m_vertexCoords.insert     ( m_vertexCoords.end(),   vertices.begin(),       vertices.end()      );
    m_textureCoords.insert    ( m_textureCoords.end(),  textureCoords.begin(),  textureCoords.end() );
}


void Chunk :: makeTop ( GLfloat x, GLfloat y, GLfloat z, const Block::Block_Base& block )
{
    std::vector<GLfloat> vertices =
    {
        x,      y + 1, z + 1,
        x + 1,  y + 1, z + 1,
        x + 1,  y + 1, z,
        x + 1,  y + 1, z,
        x,      y + 1, z,
        x,      y + 1, z + 1,
    };

    std::vector<GLfloat> textureCoords = m_p_atlas->getTextureCoords( block.getTextureTop() );

    m_vertexCoords.insert     ( m_vertexCoords.end(),   vertices.begin(),       vertices.end()      );
    m_textureCoords.insert    ( m_textureCoords.end(),  textureCoords.begin(),  textureCoords.end() );
}

void Chunk::makeLeft(GLfloat x, GLfloat y, GLfloat z, const Block::Block_Base& block)
{
    std::vector<GLfloat> vertices =
    {
        x, y,       z,
        x, y,       z + 1,
        x, y + 1,   z + 1,
        x, y + 1,   z + 1,
        x, y + 1,   z,
        x, y,       z,
    };

    std::vector<GLfloat> textureCoords = m_p_atlas->getTextureCoords( block.getTextureSide() );

    m_vertexCoords.insert     ( m_vertexCoords.end(),   vertices.begin(),       vertices.end()      );
    m_textureCoords.insert    ( m_textureCoords.end(),  textureCoords.begin(),  textureCoords.end() );
}

void Chunk::makeRight(GLfloat x, GLfloat y, GLfloat z, const Block::Block_Base& block)
{
    std::vector<GLfloat> vertices =
    {
        x + 1, y,       z + 1,
        x + 1, y,       z,
        x + 1, y + 1,   z,
        x + 1, y + 1,   z,
        x + 1, y + 1,   z + 1,
        x + 1, y,       z + 1,
    };

    std::vector<GLfloat> textureCoords = m_p_atlas->getTextureCoords( block.getTextureSide() );

    m_vertexCoords.insert     ( m_vertexCoords.end(),   vertices.begin(),       vertices.end()      );
    m_textureCoords.insert    ( m_textureCoords.end(),  textureCoords.begin(),  textureCoords.end() );
}

void Chunk::makeBack(GLfloat x, GLfloat y, GLfloat z, const Block::Block_Base& block)
{
    std::vector<GLfloat> vertices =
    {
        x + 1,  y,      z,
        x,      y,      z,
        x,      y + 1,  z,
        x,      y + 1,  z,
        x + 1,  y + 1,  z,
        x + 1,  y,      z,
    };

    std::vector<GLfloat> textureCoords = m_p_atlas->getTextureCoords( block.getTextureSide() );

    m_vertexCoords.insert     ( m_vertexCoords.end(),   vertices.begin(),       vertices.end()      );
    m_textureCoords.insert    ( m_textureCoords.end(),  textureCoords.begin(),  textureCoords.end() );
}

void Chunk::makeBottom(GLfloat x, GLfloat y, GLfloat z, const Block::Block_Base& block)
{
    std::vector<GLfloat> vertices =
    {
        x,      y, z,
        x + 1,  y, z,
        x + 1,  y, z + 1,
        x + 1,  y, z + 1,
        x,      y, z + 1,
        x,      y, z
    };

    std::vector<GLfloat> textureCoords = m_p_atlas->getTextureCoords( block.getTextureBottom() );

    m_vertexCoords.insert     ( m_vertexCoords.end(),   vertices.begin(),       vertices.end()      );
    m_textureCoords.insert    ( m_textureCoords.end(),  textureCoords.begin(),  textureCoords.end() );
}
