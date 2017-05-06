#include "CSection.h"

#include <iostream>

#include "../World_Constants.h"
#include "CMap.h"

#include "../../Util/Random.h"

namespace Chunk
{
    const Section::Layer Section::errorLayer;

    Section::Section(const Chunklet_Position& position, Map& map, Full_Chunk& fullChunk)
    :   m_position      (position)
    ,   m_meshBuilder   (*this)
    ,   mp_chunks       (&map)
    ,   m_parentChunk   (&fullChunk)
    ,   m_aabb          ({CHUNK_SIZE, CHUNK_SIZE, CHUNK_SIZE})

    ,   made            (false)
    ,   buffered        (false)
    ,   prepForBuild    (false)
    {
        m_aabb.update({ position.x * CHUNK_SIZE,
                        position.y * CHUNK_SIZE,
                        position.z * CHUNK_SIZE});
    }

    void Section::makeMesh()
    {
        for (int x = -1; x <= 1; x++)
        {
            for (int z = -1; z <= 1; z++)
            {
                mp_chunks->addChunk({m_position.x + x, m_position.z + z}, true);
            }
        }

        m_meshBuilder.generateMesh(m_meshes);
        made = true;

        buffered = false;
    }

    void Section::bufferMesh()
    {
        m_meshes.buffer();
        buffered = true;
    }

    void Section::tick(World& world)
    {
        ///@TODO Why the heck is this crashing
        /*
        for (int i = 0; i < 3; i++)
        {

            std::cout << "Called the update " << i << std::endl;
            int32_t x = Random::intInRange(0, CHUNK_SIZE - 1) + m_position.x * CHUNK_SIZE;
            int32_t y = Random::intInRange(0, CHUNK_SIZE - 1) + m_position.y * CHUNK_SIZE;
            int32_t z = Random::intInRange(0, CHUNK_SIZE - 1) + m_position.z * CHUNK_SIZE;

            std::cout << "X Y Z " << x << " " << y << " " << z << "\n";

            m_blocks.at(x, y, z).getType().tick(world, {x, y, z});
        }
        std::cout << "End\n";
        */
    }

    const Chunklet_Position& Section::getPosition() const   { return m_position;        }
    const Meshes& Section::getMeshes()              const   { return m_meshes;          }
    const AABB& Section::getAABB()                  const   { return m_aabb;            }
    const Full_Chunk& Section::getParentChunk()      const  { return *m_parentChunk;    }
    Full_Chunk& Section::getParentChunk()                   { return *m_parentChunk;    }

}



