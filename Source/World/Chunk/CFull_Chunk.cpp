#include "CFull_Chunk.h"

#include "../World_Constants.h"

namespace Chunk
{
    Full_Chunk::Full_Chunk(World& world, const Position& position)
    :   mp_world    (&world)
    ,   m_position  (position)
    {

    }

    CBlock Full_Chunk::getBlock(const Block::Position& position)
    {
        int32_t yPositionSection = position.y / CHUNK_SIZE;
        if (yPositionSection > (int32_t)m_chunkSections.size() - 1)
        {
            return Block::ID::Air;
        }
        else
        {

        }
        ///@TODO This
            return Block::ID::Air;
    }

    const Position& Full_Chunk::getPosition() const
    {
        return m_position;
    }

}
