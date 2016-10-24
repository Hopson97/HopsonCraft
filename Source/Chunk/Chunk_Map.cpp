#include "Chunk_Map.h"

#include "Maths/Matrix_Maths.h"
#include "Camera.h"

Chunk_Map::Chunk_Map()
:   m_blockTextures ("Block_Texture_Atlas", 1024, 32)
{
    int testSize = 8;
    for (int x = 0 ; x < testSize ; x++) {
        for (int z = 0 ; z < testSize ; z++) {
            addChunk({x, z});
        }
    }
    for (auto& chunk : m_chunks) {
        chunk.second->generateMesh();
        chunk.second->bufferMesh();
    }
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
    for (auto& chunk : m_chunks) {
        m_renderer.processChunk(*chunk.second.get());
    }
    m_renderer.render(camera);
}

void Chunk_Map::mangageChunk()
{

}
