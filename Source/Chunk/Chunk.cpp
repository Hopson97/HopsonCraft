#include "Chunk.h"

#include <iostream>

#include "D_Blocks.h"
#include "Texture.h"
#include "Chunk_Map.h"
#include "Random.h"

Chunk::Chunk(const Chunk_Position& position, Chunk_Map& chunkMap, const Texture_Atlas& blockAtlas)
:   m_location      (position)
,   m_glPosition    (position.x * SIZE, 0, position.z * SIZE)
,   m_p_chunkMap    (&chunkMap)
,   m_p_atlas       (&blockAtlas)
,   m_layers        (Random::integer(5, 6))
,   m_mesh          (*this, m_layers)
{
    setBlockData();
}

const Texture_Atlas& Chunk::getAtlas() const
{
    return *m_p_atlas;
}

void Chunk::setBlockData()
{
    for (unsigned y = 0 ; y < m_layers.size() - 1 ; y++) {
        for (unsigned z = 0 ; z < SIZE ; z++) {
            for (unsigned x = 0 ; x < SIZE ; x++) {
                if (y == m_layers.size() - 2)
                    m_layers.at(y).setBlock(Block::grass, {x,z});
                else if (y < m_layers.size() - 2 && y >= m_layers.size() - 5)
                    m_layers.at(y).setBlock(Block::dirt, {x,z});
                else
                    m_layers.at(y).setBlock(Block::stone, {x,z});
            }
        }
    }
}

const Chunk_Mesh& Chunk::getMesh() const
{
    return m_mesh;
}

void Chunk::generateMesh ()
{
    m_mesh.generateMesh();
}

void Chunk::bufferMesh()
{
    m_mesh.bufferMesh();
}

const Vector3& Chunk::getGlPosition() const
{
    return m_glPosition;
}

const Block::Block_Base& Chunk::getBlock(int x, int y, int z) const
{
    if ((unsigned)y > m_layers.size() - 1) {
        return Block::air;
    }
    else if ( y < 0) {
        return Block::air;
    }

    if (x == SIZE) {
        Chunk_Position pos (m_location.x + 1, m_location.z);
        if (m_p_chunkMap->getChunkAt(pos)) {
            return m_p_chunkMap->getChunkAt(pos)->getBlock(0, y, z);
        }
    }
    else if (z == SIZE) {
        Chunk_Position pos (m_location.x, m_location.z + 1);
        if (m_p_chunkMap->getChunkAt(pos)) {
            return m_p_chunkMap->getChunkAt(pos)->getBlock(x, y, 0);
        }
    }
    else if (x == -1) {
        Chunk_Position pos (m_location.x - 1, m_location.z);
        if (m_p_chunkMap->getChunkAt(pos)) {
            return m_p_chunkMap->getChunkAt(pos)->getBlock(SIZE - 1, y, z);
        }
    }
    else if (z == -1) {
        Chunk_Position pos (m_location.x, m_location.z - 1);
        if (m_p_chunkMap->getChunkAt(pos)) {
            return m_p_chunkMap->getChunkAt(pos)->getBlock(x, y, SIZE - 1);
        }
    } else {
        try {
            return m_layers.at(y).getBlock({x, z});
        } catch (std::out_of_range& e) {
            return Block::air;
        }
    }
    return Block::air;
}


void Chunk::addLayer()
{
    m_layers.emplace_back(Chunk_Layer());
}
