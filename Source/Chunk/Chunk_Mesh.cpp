#include "Chunk_Mesh.h"

#include "Chunk.h"
#include "Texture.h"
#include "Texture_Atlas.h"
#include "Loader.h"

#include <iostream>

void Chunk_Mesh::Chunk_Mesh_Part::addVerticies(const std::vector<GLfloat>& verticies )
{
    vertexCoords.insert(vertexCoords.end(), verticies.begin(), verticies.end());
}

void Chunk_Mesh::Chunk_Mesh_Part::addUvCoords (const std::vector<GLfloat>& coords)
{
    textureCoords.insert(textureCoords.end(), coords.begin(), coords.end());
}

Chunk_Mesh::Chunk_Mesh(const Chunk& chunk)
:   m_p_chunk (&chunk)
{}

void Chunk_Mesh::bufferMesh()
{
    if(!m_solidPart.model.getVertexCount() == 0 ) std::cout << "NOT ZERO" << m_solidPart.model.getVertexCount() << std::endl;
    m_solidPart.model.addData(Loader::loadArrayMesh(m_solidPart.vertexCoords, m_solidPart.textureCoords));
    m_solidPart.textureCoords.clear();
    m_solidPart.vertexCoords.clear();

    m_waterPart.model.addData(Loader::loadArrayMesh(m_waterPart.vertexCoords, m_waterPart.textureCoords));
    m_waterPart.textureCoords.clear();
    m_waterPart.vertexCoords.clear();
}

const Chunk_Mesh::Chunk_Mesh_Part& Chunk_Mesh::getSolidPart() const
{
    return m_solidPart;
}

const Chunk_Mesh::Chunk_Mesh_Part& Chunk_Mesh::getWaterPart() const
{
    return m_waterPart;
}

void Chunk_Mesh::generateMesh()
{
    for (int y = 0 ; y < Chunk::HEIGHT ; y++)
    {
        for (int z = 0 ; z < Chunk::SIZE ; z++)
        {
            for (int x = 0 ; x < Chunk::SIZE ; x++)
            {
                if (m_p_chunk->getBlock(x, y, z).getID() == Block::ID::Air)
                {
                    continue;
                }
                addBlockMesh (x, y, z, m_p_chunk->getBlock(x, y, z));
            }
        }
    }
}

Chunk_Mesh::Chunk_Mesh_Part& Chunk_Mesh::getPart(const Block::Block_Base& block)
{
    if (block.getID() == Block::ID::Water)
    {
        return m_waterPart;
    }
    else
    {
        return m_solidPart;
    }
}



void Chunk_Mesh::addBlockMesh (float x, float y, float z, const Block::Block_Base& block)
{

    if (shouldMakeMesh(x, y + 1, z, block))
    {
        addBlockTopToMesh   (x, y, z, block);
    }
    if (shouldMakeMesh(x, y -1, z, block) && (int)y != 0)
    {
        addBlockBottomToMesh(x, y, z, block);
    }
    if (shouldMakeMesh(x - 1, y, z, block))
    {
        addBlockLeftToMesh  (x, y, z, block);
    }
    if (shouldMakeMesh(x + 1, y, z, block))
    {
        addBlockRightToMesh (x, y, z, block);
    }
    if (shouldMakeMesh(x, y, z + 1, block))
    {
        addBlockFrontToMesh (x, y, z, block);
    }
    if (shouldMakeMesh(x, y, z - 1, block))
    {
        addBlockBackToMesh  (x, y, z, block);
    }
}

bool Chunk_Mesh::shouldMakeMesh(int x, int y, int z, const Block::Block_Base& block)
{
    return   ( m_p_chunk->getBlock(x, y, z).getID() == Block::ID::Air) ||
             (!m_p_chunk->getBlock(x, y, z).isOpaque() && m_p_chunk->getBlock(x, y, z).getID() != block.getID());
}


void Chunk_Mesh::addBlockTopToMesh(float x, float y, float z, const Block::Block_Base& block)
{
    getPart(block).addVerticies
    (
    {
        x,      y + 1, z + 1,
        x + 1,  y + 1, z + 1,
        x + 1,  y + 1, z,
        x + 1,  y + 1, z,
        x,      y + 1, z,
        x,      y + 1, z + 1,
    });
    getPart(block).addUvCoords(m_p_chunk->getAtlas().getTextureCoords(block.getTextureTop()));
}

void Chunk_Mesh::addBlockBottomToMesh(float x, float y, float z, const Block::Block_Base& block)
{
    getPart(block).addVerticies
    (
    {
        x,      y, z,
        x + 1,  y, z,
        x + 1,  y, z + 1,
        x + 1,  y, z + 1,
        x,      y, z + 1,
        x,      y, z
    });
    getPart(block).addUvCoords(m_p_chunk->getAtlas().getTextureCoords(block.getTextureBottom()));
}

void Chunk_Mesh::addBlockLeftToMesh(float x, float y, float z, const Block::Block_Base& block)
{
    getPart(block).addVerticies
    (
    {
        x, y,       z,
        x, y,       z + 1,
        x, y + 1,   z + 1,
        x, y + 1,   z + 1,
        x, y + 1,   z,
        x, y,       z,
    });
    getPart(block).addUvCoords(m_p_chunk->getAtlas().getTextureCoords(block.getTextureSide()));
}

void Chunk_Mesh::addBlockRightToMesh(float x, float y, float z, const Block::Block_Base& block)
{
    getPart(block).addVerticies
    (
    {
        x + 1, y,       z + 1,
        x + 1, y,       z,
        x + 1, y + 1,   z,
        x + 1, y + 1,   z,
        x + 1, y + 1,   z + 1,
        x + 1, y,       z + 1,
    });
    getPart(block).addUvCoords(m_p_chunk->getAtlas().getTextureCoords(block.getTextureSide()));
}

void Chunk_Mesh::addBlockFrontToMesh(float x, float y, float z, const Block::Block_Base& block)
{
    getPart(block).addVerticies
    (
    {
        x,      y,      z + 1,
        x + 1,  y,      z + 1,
        x + 1,  y + 1,  z + 1,
        x + 1,  y + 1,  z + 1,
        x,      y + 1,  z + 1,
        x,      y,      z + 1,
    });
    getPart(block).addUvCoords(m_p_chunk->getAtlas().getTextureCoords(block.getTextureSide()));
}

void Chunk_Mesh::addBlockBackToMesh(float x, float y, float z, const Block::Block_Base& block)
{
    getPart(block).addVerticies
    (
    {
        x + 1,  y,      z,
        x,      y,      z,
        x,      y + 1,  z,
        x,      y + 1,  z,
        x + 1,  y + 1,  z,
        x + 1,  y,      z,
    });
    getPart(block).addUvCoords(m_p_chunk->getAtlas().getTextureCoords(block.getTextureSide()));
}
