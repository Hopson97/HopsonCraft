#include "CSection.h"

#include <iostream>

#include "../World_Constants.h"
#include "CMap.h"

namespace Chunk
{
    Section::Layer Section::errorLayer;
    bool errorSet = false;

    Section::Section(const Chunklet_Position& position, Map& map)
    :   m_position      (position)
    ,   m_meshBuilder   (*this)
    ,   mp_chunks       (&map)
    {
        if(!errorSet)
        {
            errorLayer.opaqueCount = 0;
        }
    }

    void Section::makeMesh()
    {
        m_meshBuilder.generateMesh(m_meshes);
        m_meshes.solidMesh.buffer();
        made = true;
    }


    Section* Section::getSection(Block::Small_Position& position)
    {
        static const sf::Vector3<int32_t> noChnage(0, 0, 0);
        auto change = noChnage;

        checkBound(position.x, change.x);
        checkBound(position.y, change.y);
        checkBound(position.z, change.z);

        if (change == noChnage)
        {
            return this;
        }
        else
        {
            Chunk::Chunklet_Position newPos = m_position + change;

            if (mp_chunks->existsAt({newPos.x, newPos.y, newPos.z}))
            {
                return mp_chunks->get({newPos.x, newPos.y, newPos.z});
            }
            else
            {
                return nullptr;
            }
        }
    }

    const Section* Section::getConstSection(Block::Small_Position& position) const
    {
        static const sf::Vector3<int32_t> noChnage(0, 0, 0);
        auto change = noChnage;

        checkBound(position.x, change.x);
        checkBound(position.y, change.y);
        checkBound(position.z, change.z);

        if (change == noChnage)
        {
            return this;
        }
        else
        {
            Chunk::Chunklet_Position newPos = m_position + change;

            if (mp_chunks->existsAt({newPos.x, newPos.y, newPos.z}))
            {
                return mp_chunks->get({newPos.x, newPos.y, newPos.z});
            }
            else
            {
                return nullptr;
            }
        }
    }

    void Section::checkBound(int8_t& pos, int32_t& change) const
    {
        if (pos > CHUNK_SIZE - 1)
        {
            change = 1;
            pos -= CHUNK_SIZE;
        }
        else if (pos < 0)
        {
            change = -1;
            pos += CHUNK_SIZE;
        }
    }

    uint32_t Section::getIndexFrom(const Block::Small_Position& position) const
    {
        return position.y *
               CHUNK_AREA + position.z *
               CHUNK_SIZE + position.x;
    }

    const Chunklet_Position& Section::getPosition()  const { return m_position; }
    const Meshes& Section::getMeshes()               const { return m_meshes;   }

    const Section::Layer& Section::getLayer(int8_t y)const
    {
        ///@TODO This to use better bounds
        if (y == -1)
        {
            const Section* chunk = mp_chunks->get({m_position.x, m_position.y - 1, m_position.z});
            if(!chunk)
            {
                return errorLayer;
            }
            else return chunk->m_layerHasAir[CHUNK_SIZE - 1];
        }
        else if (y == CHUNK_SIZE)
        {
            const Section* chunk = mp_chunks->get({m_position.x, m_position.y + 1, m_position.z});
            if(!chunk)
            {
                return errorLayer;
            }
            else return chunk->m_layerHasAir[0];
        }
        return m_layerHasAir[y];
    }

    const Section* Section::getAdjacentSection(const Vector2& change) const
    {
        return mp_chunks->get({ m_position.x + change.x,
                                m_position.y,
                                m_position.z + change.y});
    }

}





















