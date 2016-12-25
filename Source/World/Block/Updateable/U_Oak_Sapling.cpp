#include "U_Oak_Sapling.h"

#include <iostream>

#include "../../../Util/Random.h"

#include "../../Chunk/Chunk.h"
#include "../../Gen/Structure.h"

namespace Block
{
    U_Oak_Sapling::U_Oak_Sapling()
    :   m_timeToGrow    (sf::seconds(1))
    { }

    bool U_Oak_Sapling::update(const Block_Location& location)
    {
        if (m_growClock.getElapsedTime() > m_timeToGrow)
        {
            m_p_chunk->giveRegenMeshFlag();
            Structure::createOak(*m_p_chunk, Block_Location{location.x, location.y - 1, location.z}, true);
            m_isDestroyed = true;
        }
        return m_isDestroyed;
    }

    void U_Oak_Sapling::breakBlock()
    { }


}
