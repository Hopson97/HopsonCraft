#include "Chunklet.h"

#include "../../Maths/Matrix_Maths.h"

Chunklet::Chunklet()
:   m_mesh  (*this)
{
    position.z -= 35;
    position.y -= 35;

    m_modelMat = Maths::createModelMatrix(*this);


    for (uint8_t y = 0; y < World_Constants::CH_SIZE; y++)
    {
        for (uint8_t x = 0; x < World_Constants::CH_SIZE; x++)
        {
            for (uint8_t z = 0; z < World_Constants::CH_SIZE; z++)
            {
                if (y != World_Constants::CH_SIZE - 1)
                    m_blocks.at(getBlockIndex({x, y, z})) = 2;
            }
        }
    }

    m_mesh.create();
}

CBlock Chunklet::getBlock(const Block::Position& pos) const
{
    //return Block::ID::Air;
    if (pos.x < 0)
    {
        return Block::ID::Air;
    }
    if (pos.x > World_Constants::CH_SIZE - 1)
    {
        return Block::ID::Air;
    }
    if (pos.z < 0)
    {
        return Block::ID::Air;
    }
    if (pos.z > World_Constants::CH_SIZE - 1)
    {
        return Block::ID::Air;
    }
    if (pos.y < 0)
    {
        return Block::ID::Air;
    }
    if (pos.y > World_Constants::CH_SIZE - 1)
    {
        return Block::ID::Air;
    }

    return m_blocks.at(getBlockIndex(pos));
}


const Chunk::Mesh& Chunklet::getMesh() const
{
    return m_mesh;
}

const Matrix4& Chunklet::getMat() const
{
    return m_modelMat;
}


uint32_t Chunklet::getBlockIndex(const Block::Position& pos) const
{
    return pos.y * World_Constants::CH_AREA + pos.z * World_Constants::CH_SIZE + pos.x;
}
