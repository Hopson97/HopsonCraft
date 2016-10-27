#include "playing_state.h"

#include <SFML/System/Clock.hpp>
#include <iostream>

#include "Block/Block.h"
#include "Display.h"
#include "Block/D_Blocks.h"
#include "Debug_Display.h"
#include "Maths/Position_Converter_Maths.h"

namespace State
{
    Playing_State::Playing_State(Application& application)
    :   Game_State          (application)
    ,   m_playerPosition    ({(int)m_player.getPosition().x / Chunk::SIZE,
                              (int)m_player.getPosition().z / Chunk::SIZE})
    ,   m_chunkMap          (m_playerPosition)
    ,   m_debugDisplay      ([&](){m_debugDisplayActive = !m_debugDisplayActive;}, sf::Keyboard::F3, 0.5)
    {

        crossHairTexture.loadFromFile("Data/Images/Crosshair.png");
        crossHairSprite.setTexture(crossHairTexture);
        crossHairSprite.setPosition(Display::get().getSize().x / 2 - crossHairSprite.getTexture()->getSize().x / 2,
                                    Display::get().getSize().y / 2 - crossHairSprite.getTexture()->getSize().y / 2);

    }

    void Playing_State::input (float dt)
    {
        m_player.input();
        m_debugDisplay.checkInput();

        static sf::Clock c;

        if (c.getElapsedTime().asSeconds() > 0.5)
        {
            auto& p = m_player.getPosition();

            int xStart = p.x - 1;
            int yStart = p.y - 1;
            int zStart = p.z - 1;

            std::vector<Vector3> positions;
            for (int y = yStart ; y <= yStart + 2 ; y++)
            {
                for (int x = xStart ; x <= xStart + 2 ; x++)
                {
                    for (int z = zStart ; z <= zStart + 2 ; z++)
                    {
                        positions.emplace_back(x, y, z);
                    }
                }
            }

            m_chunkMap.setBlocks(Block::air, positions);
        }
/*
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            float   x = m_player.getPosition().x,
                    y = m_player.getPosition().y + 0.85,
                    z = m_player.getPosition().z;

            float oldX, oldY, oldZ;

            for (int dist = 0 ; dist < 120 ; dist++)
            {
                x += -sin(glm::radians(m_player.getRotation().x));
                y +=  tan(glm::radians(m_player.getRotation().y));
                z += -cos(glm::radians(m_player.getRotation().z));

                if (m_chunkMap.isSolidBlockAt({x, y, z}))
                {
                    m_chunkMap.setBlock(Block::air, {x, y, z});
                    break;
                }
            }
        }
        */
    }

    void Playing_State::update (float dt)
    {
        Debug_Display::addPlayerPosition(m_player.getPosition());

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
        Display::sfDraw(crossHairSprite);
    }
}

