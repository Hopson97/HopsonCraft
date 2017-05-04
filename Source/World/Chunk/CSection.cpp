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
        made = true;
        buffered = false;
    }

    void Section::bufferMesh()
    {
        m_meshes.solidMesh.buffer();
        m_meshes.floraMesh.buffer();
        m_meshes.liquidMesh.buffer();
        buffered = true;
    }

    const Chunklet_Position& Section::getPosition() const   { return m_position;        }
    const Meshes& Section::getMeshes()              const   { return m_meshes;          }
    const AABB& Section::getAABB()                  const   { return m_aabb;            }
    const Full_Chunk& Section::getParentChunk()      const  { return *m_parentChunk;    }
    Full_Chunk& Section::getParentChunk()                   { return *m_parentChunk;    }

}



