#include "CFull_Chunk.h"

#include "../World_Constants.h"
#include "../../Maths/General_Maths.h"

namespace Chunk
{
    Full_Chunk::Full_Chunk(World& world, Map& map, const Position& position)
    :   mp_world    (&world)
    ,   mp_chunkMap (&map)
    ,   m_position  (position)
    {
        for (int i = 0 ; i < 5 ; i++)
        {
            addSection();
        }
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
            ///@TODO Change to use operator []
            return m_chunkSections.at(yPositionSection)
                ->qGetBlock(Maths::blockToSmallBlockPos(position));
        }
    }

    const Position& Full_Chunk::getPosition() const
    {
        return m_position;
    }

    Section* Full_Chunk::getSection(int32_t index)
    {
        if (index > m_sectionCount - 1 || index < 0)
        {
            return nullptr;
        }
        else
        {
            ///@TODO Change to use operator []
            return m_chunkSections.at(index).get();
        }
    }


    void Full_Chunk::addSection()
    {
        Chunklet_Position position (m_position.x, m_sectionCount++, m_position.y);

        m_chunkSections.push_back(std::make_unique<Section>(position, *mp_chunkMap));
    }


}
