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

        static sf::Clock powerManClock;
        static sf::Clock breakBlockClock;
        static bool powerMode = false;
        static Toggle_Key powerManToggle ([&](){powerMode = !powerMode;}, sf::Keyboard::P, 1.5f);

        powerManToggle.checkInput();

        if (powerMode)
        if (powerManClock.getElapsedTime().asSeconds() > 0.03)
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
            powerManClock.restart();
            m_chunkMap.setBlocks(Block::air, positions);
        }

        //Block breaking and placing
        if (breakBlockClock.getElapsedTime().asSeconds() > 0.05)
        {
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Mouse::isButtonPressed(sf::Mouse::Right))
            {
                Vector3 change;
                Vector3 rayEnd;
                Vector3 oldRayEnd;

                auto yaw    = glm::radians(m_player.getRotation().y + 90);
                auto pitch  = glm::radians(m_player.getRotation().x);

                for (float dist = 0.0f ; dist < 6 ; dist += 0.001f )
                {
                    change.x -= cos (yaw)   * dist;
                    change.z -= sin (yaw)   * dist;
                    change.y -= tan (pitch) * dist; //For the Y component, "dist" is the "adjecent" side of the
                                                    //vector, hence the use of tan as tan(x) = opp / adj so opp aka
                                                    //the down vecor is adj * tan(x)
                    rayEnd = change + m_player.getPosition();


                    if (m_chunkMap.isSolidBlockAt(rayEnd))
                    {
                        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                        {
                            m_chunkMap.setBlock(Block::air, rayEnd);
                        }
                        else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
                        {
                            m_chunkMap.setBlock(Block::stone, oldRayEnd);
                        }
                        break;
                    }
                    else
                    {
                        oldRayEnd = rayEnd;
                    }
                }
                breakBlockClock.restart();
            }
        }

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

