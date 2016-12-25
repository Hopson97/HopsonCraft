#include "U_Cactus.h"

#include "../../../Util/Random.h"

#include "../../Chunk/Chunk.h"
#include "../../Gen/Structure.h"


namespace Block
{
    U_Cactus::U_Cactus()
    :   m_timeToGrow    (sf::seconds(2))
    { }

    bool U_Cactus::update(const Block_Location& location)
    {
        if (m_growClock.getElapsedTime() > m_timeToGrow)
        {
            m_p_chunk->giveRegenMeshFlag();
            m_p_chunk->addBlock({location.x, location.y + 1, location.z}, Block::cactus, false);
            m_isDestroyed = true;
            m_growClock.restart();
        }
        return m_isDestroyed;
    }

    void U_Cactus::breakBlock()
    { }
}
