#include "Chunk_Map.h"

#include "Matrix_Math.h"

Chunk_Map::Chunk_Map()
:   m_blockTextures ("Block_Texture_Atlas", 1024, 32)
,   shader     ("Basic_Vertex_Shader", "Basic_Fragment_Shader")
{
    int testSize = 8;
    for (int x = 0 ; x < testSize ; x++) {
        for (int z = 0 ; z < testSize ; z++) {
            addChunk({x, z});
        }
    }

    shader.useProgram();
    shader.loadMatrix4(glGetUniformLocation(shader.m_shaderProgram, "projectionMatrix"),
                       Maths::createPerspectiveMatrix());
}

Chunk* Chunk_Map::getChunkAt (const Chunk_Position& location)
{
    if (m_chunks.find(location) != m_chunks.end()) {
        return &*m_chunks.at(location);
    } else {
        return nullptr;
    }
}

void Chunk_Map::addChunk(const Chunk_Position& location)
{
    if (!getChunkAt(location)) {
        m_chunks[location] = std::make_unique<Chunk>(location, *this, m_blockTextures);
    }
}

void Chunk_Map::draw(const Camera& camera)
{

}

void Chunk_Map::mangageChunk()
{

}
