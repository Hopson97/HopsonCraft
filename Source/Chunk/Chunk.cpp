#include "Chunk.h"

#include "D_Blocks.h"
#include "Texture.h"

Chunk::Chunk(const Texture_Atlas& blockAtlas)
:   m_p_atlas   (&blockAtlas)
,   m_layers    (SIZE * SIZE)
,   m_mesh      (*this, m_layers)
{

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
                m_layers.at(y).setBlock(Block::grass, {x,z});
            }
        }
    }
}

void Chunk::bufferMesh()
{
    m_mesh.generateMesh();
    m_mesh.bufferMesh();
}

void Chunk::bind()
{
    m_mesh.bind();
}

void Chunk::draw()
{
    m_mesh.draw();
}



const Block::Block_Base& Chunk::getBlock(int x, int y, int z) const
{
    if ( y == -1 || y > m_layers.size() -1 ) {
        return Block::air;
    }
    if (x == SIZE) {
        return Block::air;
    }
    else if (z == SIZE) {
        return Block::air;
    }
    else if (x == -1) {
        return Block::air;
    }
    else if (z == -1) {
        return Block::air;
    } else {
        try {
            return m_layers.at(y).getBlock({x, z});
        } catch (std::out_of_range& e) {
            //std::cout << "Warning: tried to access OOB block!" << std::endl;
            return Block::air;
        }
    }
}


void Chunk::addLayer()
{
    m_layers.emplace_back(Chunk_Layer());
}
