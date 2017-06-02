#include "Section.h"

#include <iostream>
#include <fstream>

#include <SFML/Network.hpp>

#include "../World_Constants.h"
#include "../World_File.h"
#include "Map.h"

#include "../../Maths/Position_Conversion.h"

#include "../../Util/Random.h"

namespace Chunk
{
    const Section::Layer Section::errorLayer;

    Section::Section(const Chunklet_Position& position, Map& map, Full_Chunk& fullChunk)
    :   m_aabb          ({CHUNK_SIZE, CHUNK_SIZE, CHUNK_SIZE})
    ,   m_position      (position)
    ,   m_pChunkMap     (&map)
    ,   m_parentChunk   (&fullChunk)
    {
        m_aabb.update({ position.x * CHUNK_SIZE,
                        position.y * CHUNK_SIZE,
                        position.z * CHUNK_SIZE});
    }

    const Section::State& Section::getStates() const
    {
        return m_states;
    }


    void Section::makeMesh()
    {
        //Adds chunks around this chunk so that the mesh
        //builder can put block faces in the correct place
        for (int x = -1; x <= 1; x++)
        {
            for (int z = -1; z <= 1; z++)
            {
                if (x == 0 && z == 0) continue;
                m_pChunkMap->addChunk({m_position.x + x, m_position.z + z}, true);
            }
        }

        m_meshes = buildMesh(*this);
        m_states.made = true;

        m_states.buffered = false;
    }

    void Section::bufferMesh()
    {
        m_meshes.buffer();
        m_states.buffered = true;
    }

    void Section::tick(World& world)
    {
        for (int i = 0; i < 3; i++)
        {
            int32_t x = Random::intInRange(0, CHUNK_SIZE - 1);
            int32_t y = Random::intInRange(0, CHUNK_SIZE - 1);
            int32_t z = Random::intInRange(0, CHUNK_SIZE - 1);

            auto worldBlockPosition =
                Maths::Convert::sectionBlockToWorldBlockPosition({x, y, z}, getPosition());

            auto& block = m_blocks.at(x, y, z);
            block.getType().tick(world, block, worldBlockPosition);
        }
    }

    const Chunklet_Position& Section::getPosition() const   { return m_position;        }
    const Meshes& Section::getMeshes()              const   { return m_meshes;          }
    const AABB& Section::getAABB()                  const   { return m_aabb;            }
    const Full_Chunk& Section::getParentChunk()     const   { return *m_parentChunk;    }
    Full_Chunk& Section::getParentChunk()                   { return *m_parentChunk;    }

    void Section::setBlock (int x, int y, int z, CBlock block)
    {
        Block::Position position(x, y, z);
        setBlock(position, block);
    }

    CBlock Section::getBlock (int x, int y, int z) const
    {
        Block::Position position(x, y, z);
        return getBlock(position);
    }

    void Section::qSetBlock (int x, int y, int z, CBlock block)
    {
        Block::Position position(x, y, z);
        qSetBlock(position, block);
    }

    CBlock  Section::qGetBlock   (int x, int y, int z) const
    {
        Block::Position position(x, y, z);
        return qGetBlock(position);
    }
}



