#include "Chunk/Chunk.h"

#include <iostream>

#include "Texture_Atlas.h"

Chunk :: Chunk_Part& Chunk :: getPart ( const Block_t& block )
{
    switch ( block.getID() )
    {
        case Block::ID::Water:
            return m_waterPart;
        default:
            return m_solidPart;
    }
}


void Chunk :: makeBlock ( GLfloat x, GLfloat y, GLfloat z, const Block_t& block )
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

void Chunk :: makeFront ( GLfloat x, GLfloat y, GLfloat z, const Block_t& block )
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

    finalizeFace( vertices, textureCoords, getPart( block ) );
}


void Chunk :: makeTop ( GLfloat x, GLfloat y, GLfloat z, const Block_t& block )
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

    finalizeFace( vertices, textureCoords, getPart( block ) );
}

void Chunk::makeLeft(GLfloat x, GLfloat y, GLfloat z, const Block_t& block)
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

    finalizeFace( vertices, textureCoords, getPart( block ) );
}

void Chunk::makeRight(GLfloat x, GLfloat y, GLfloat z, const Block_t& block)
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

    finalizeFace( vertices, textureCoords, getPart( block ) );
}

void Chunk::makeBack(GLfloat x, GLfloat y, GLfloat z, const Block_t& block)
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

    finalizeFace( vertices, textureCoords, getPart( block ) );
}

void Chunk::makeBottom(GLfloat x, GLfloat y, GLfloat z, const Block_t& block)
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

    finalizeFace( vertices, textureCoords, getPart( block ) );
}

void Chunk::finalizeFace (  const std::vector<GLfloat>& verticies,
                            const std::vector<GLfloat>& textureCoords,
                            Chunk_Part& part )
{
    part.vertexData.insert  ( part.vertexData.end(),    verticies.begin(),      verticies.end()     );
    part.textureData.insert ( part.textureData.end(),   textureCoords.begin(),  textureCoords.end() );
}
