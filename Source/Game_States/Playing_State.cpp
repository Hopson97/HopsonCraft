#include "playing_state.h"

#include <SFML/System/Clock.hpp>
#include <iostream>

#include "Block/Block.h"
#include "Display.h"
#include "Block/D_Blocks.h"
#include "Debug_Display.h"

namespace State
{
    Playing_State::Playing_State(Application& application)
    :   Game_State          (application)
    ,   m_playerPosition    ({(int)m_player.getPosition().x / Chunk::SIZE,
                              (int)m_player.getPosition().z / Chunk::SIZE})
    ,   m_chunkMap          (m_playerPosition)
    ,   m_debugDisplay      ([&](){m_debugDisplayActive = !m_debugDisplayActive;}, sf::Keyboard::F3, 0.5)
    {
    }

    void Playing_State::input (float dt)
    {
        m_player.input();
        m_debugDisplay.checkInput();
    }

    void Playing_State::update (float dt)
    {
        m_player.update(dt);
        m_playerPosition = {(int)m_player.getPosition().x / Chunk::SIZE,
                            (int)m_player.getPosition().z / Chunk::SIZE};

        m_chunkMap.checkChunks();//This must be the last thing to happen in the update function here!
    }

    void Playing_State::draw (float dt)
    {
        m_chunkMap.draw(m_renderer);

        m_renderer.render(m_player.getCamera());

    }

    void Playing_State::sfDraw(float dt)
    {
        if (m_debugDisplayActive)
        {
            Debug_Display::draw();
        }
    }
}

