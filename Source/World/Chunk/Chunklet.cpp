#include "Chunklet.h"

#include "../../Maths/Matrix_Maths.h"
#include "../../Util/Random.h"

#include "CMap.h"

#include <iostream>

Chunklet::Chunklet(const Chunk::Chunklet_Position& pos,
                   Chunk::Map& map)
:   m_mesh          (*this)
,   m_pos           (pos)
,   m_p_chunkMap    (&map)
{
    position.x = pos.x * World_Constants::CH_SIZE;
    position.z = pos.z * World_Constants::CH_SIZE;
    position.y = pos.y * World_Constants::CH_SIZE;

    m_modelMat = Maths::createModelMatrix(*this);


    for (uint8_t y = 0; y < World_Constants::CH_SIZE; y++)
    {
        for (uint8_t x = 0; x < World_Constants::CH_SIZE; x++)
        {
            for (uint8_t z = 0; z < World_Constants::CH_SIZE; z++)
            {
                if (y != World_Constants::CH_SIZE - 1)
                    m_blocks.at(getBlockIndex({(int8_t)x, (int8_t)y, (int8_t)z})) = 2;
/*
                auto val = Random::intInRange(0, 10);

                val = val > 7? 1 : 0;

                if (y != World_Constants::CH_SIZE - 1 && val == 1)
                    val = 2;

                m_blocks.at(getBlockIndex({x, y, z})) = val;
*/
            }
        }
    }
}

void Chunklet::createMesh()
{
    m_mesh.create();
}

CBlock Chunklet::getBlock(const Block::Position& pos) const
{/*
    const auto& chunklet = getChunklet(pos);

    if (chunklet == this)
        return qGetBlock(pos);

    else
    {
        //auto offset = getPosition() - chunklet->getPosition();

        if (chunklet)
        {
            std::cout << "not rip" << std::endl;
            //return chunklet->qGetBlock(ncPos);
            return Block::ID::Dirt;
        }
        else
        {
            return Block::ID::Air;
        }
    }*/

    if (pos.x < 0)
    {
        return Block::ID::Air;
    }
    else if (pos.x > World_Constants::CH_SIZE - 1)
    {
        return Block::ID::Air;
    }
    else if (pos.z < 0)
    {
        return Block::ID::Air;
    }
    else if (pos.z > World_Constants::CH_SIZE - 1)
    {
        return Block::ID::Air;
    }
    else if (pos.y < 0)
    {
        return Block::ID::Air;
    }
    else if (pos.y > World_Constants::CH_SIZE - 1)
    {
        return Block::ID::Air;
    }
    else
    {
        return qGetBlock(pos);
    }
}

CBlock Chunklet::qGetBlock(const Block::Position& pos) const
{
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

const Chunk::Chunklet_Position& Chunklet::getPosition() const
{
    return m_pos;
}

uint32_t Chunklet::getBlockIndex(const Block::Position& pos) const
{
    return pos.y * World_Constants::CH_AREA + pos.z * World_Constants::CH_SIZE + pos.x;
}
