#include "Chunk.h"

#include <iostream>

#include "Block.h"
#include "Texture_Atlas.h"

void Chunk :: makeBlock ( GLfloat x, GLfloat y, GLfloat z, const Block::Block_Base& block )
{
    if ( getBlock( x, y + 1, z).getID() == Block::ID::Air )
    {
        makeTop( x, y, z, block );
    }
    if ( getBlock( x, y - 1, z).getID() == Block::ID::Air )
    {
        makeBottom( x, y, z, block );
    }


    if ( getBlock( x, y, z + 1).getID() == Block::ID::Air )
    {
        makeFront( x, y, z, block );
    }
    if ( getBlock( x, y, z - 1).getID() == Block::ID::Air )
    {
        makeBack( x, y, z, block );
    }


    if ( getBlock( x - 1, y, z).getID() == Block::ID::Air )
    {
        makeLeft( x, y, z, block );
    }
    if ( getBlock( x + 1, y, z).getID() == Block::ID::Air )
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
