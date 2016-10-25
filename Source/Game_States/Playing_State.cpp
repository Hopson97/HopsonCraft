#include "playing_state.h"

#include <SFML/System/Clock.hpp>

#include "D_Blocks.h"
#include "Display.h"

namespace State
{
    Playing_State::Playing_State(Application& application)
    :   Game_State          (application)
    ,   m_playerPosition    ({(int)m_player.getPosition().x / Chunk::SIZE,
                              (int)m_player.getPosition().z / Chunk::SIZE})
    ,   m_chunkMap          (m_playerPosition)
    {
    }

    void Playing_State::input  (float dt)
    {
        m_player.input();
    }

    void Playing_State::update (float dt)
    {
        m_player.update(dt);
        m_playerPosition = {(int)m_player.getPosition().x / Chunk::SIZE,
                            (int)m_player.getPosition().z / Chunk::SIZE};

        m_chunkMap.checkChunks();//This must be the last thing to happen in the update function here!
    }

    void Playing_State::draw   (float dt)
    {
        m_chunkMap.draw(m_player.getCamera(), m_renderer);
    }
}
