#include "CSection.h"

#include <iostream>

#include "../World_Constants.h"
#include "CMap.h"

namespace Chunk
{
    const Section::Layer Section::errorLayer;

    Section::Section(const Chunklet_Position& position, Map& map, Full_Chunk& fullChunk)
    :   m_position      (position)
    ,   m_meshBuilder   (*this)
    ,   mp_chunks       (&map)
    ,   m_parentChunk   (&fullChunk)
    ,   m_aabb          ({CHUNK_SIZE, CHUNK_SIZE, CHUNK_SIZE})
    {
        m_aabb.update({ position.x * CHUNK_SIZE,
                        position.y * CHUNK_SIZE,
                        position.z * CHUNK_SIZE});
    }

    void Section::makeMesh()
    {
        m_meshBuilder.generateMesh(m_meshes);

        ///@TODO Move these buffer calls to new function
        m_meshes.solidMesh.buffer();
        m_meshes.floraMesh.buffer();
        m_meshes.liquidMesh.buffer();
        made = true;
    }




    const Chunklet_Position& Section::getPosition() const   { return m_position;        }
    const Meshes& Section::getMeshes()              const   { return m_meshes;          }
    const AABB& Section::getAABB()                  const   { return m_aabb;            }
    const Full_Chunk& Section::getParentChunk()      const  { return *m_parentChunk;    }


    const Section::Layer& Section::getLayer(int8_t y)const
    {
        ///@TODO This to use better bounds
        if (y == -1)
        {
            const auto& chunk = mp_chunks->get({m_position.x, m_position.y - 1, m_position.z});
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
        else
        {
            return m_layerHasAir[y];
        }
    }


    const Section* Section::getAdjacentSection(const Vector2& change) const
    {
        return mp_chunks->get({ m_position.x + (int32_t)change.x,
                                m_position.y,
                                m_position.z + (int32_t)change.y});
    }
}





















