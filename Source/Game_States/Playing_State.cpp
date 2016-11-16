#include "playing_state.h"

#include <SFML/System/Clock.hpp>
#include <iostream>
#include <fstream>

#include "../World/Block/D_Blocks.h"
#include "../World/Block/Block.h"

#include "../Util/Display.h"
#include "../Util/Debug_Display.h"
#include "../Util/Directory_Creator.h"
#include "../Util/Noise_Generator.h"

#include "../Maths/Position_Converter_Maths.h"
#include "../Maths/Ray.h"
#include "../Maths/General_Maths.h"

#include "../Renderer/Master_Renderer.h"



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


        Directory::create("Worlds/" + std::to_string(Noise::getSeed()));

        std::ifstream inFile("Worlds/" + std::to_string(Noise::getSeed() ) + "/World_Info.data");
        if (inFile.is_open())
        {
            int x, y, z;
            inFile >> x >> y >> z;
            m_player.setPosition({x + 0.5, y + 0.5, z + 0.5});
        }
    }

    void Playing_State::input (float dt)
    {
        m_player.input();
        m_debugDisplay.checkInput();

        static sf::Clock breakBlockClock;

        //Block breaking and placing
        if (breakBlockClock.getElapsedTime().asSeconds() > 0.2)
        {
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Mouse::isButtonPressed(sf::Mouse::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::P))
            {

                auto oldRayEnd = m_player.getPosition();

                Maths::Ray ray(m_player.getRotation().y + 90,
                               m_player.getRotation().x,
                               m_player.getPosition());

                for (auto dist = 0.0f ; dist < 1.0f ; dist += 0.001f )
                {
                    ray.step(dist);

                    //Delta/ Difference
                    auto d = ray.getEndPoint() - m_player.getPosition();

                    if (Maths::getLength({d.x, d.y, d.z}) > 6.75) break;
                    if (Maths::getLength({d.x, d.y, d.z}) > 6.75) break;

                    const auto& worldPoint = Maths::worldToBlockPosition(ray.getEndPoint());

                    if (m_chunkMap.getBlockAt(ray.getEndPoint()).getPhysicalState() == Block::Physical_State::Solid ||
                        m_chunkMap.getBlockAt(ray.getEndPoint()).getPhysicalState() == Block::Physical_State::Flora)
                    {
                        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::O))
                        {
                            if (worldPoint != Maths::worldToBlockPosition(m_player.getPosition()))
                                m_chunkMap.setBlock(Block::air, ray.getEndPoint());
                        }
                        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
                        {
                            if (worldPoint != Maths::worldToBlockPosition(m_player.getPosition()))
                                m_chunkMap.makeExplosion(ray.getEndPoint(), 5);
                        }
                        else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
                        {
                            if (Maths::worldToBlockPosition(oldRayEnd) != Maths::worldToBlockPosition(m_player.getPosition()))
                                m_chunkMap.setBlock(m_player.getHeldBlock(), oldRayEnd);
                        }
                        break;
                    }
                    else
                    {
                        oldRayEnd = ray.getEndPoint();
                    }
                }
                breakBlockClock.restart();
            }
        }
    }

    void Playing_State::update  (float dt, Camera& camera)
    {
        Debug_Display::addPlayerPosition(m_player.getPosition());

        m_player.update(dt, camera);
        m_playerPosition = {(int)m_player.getPosition().x / Chunk::SIZE,
                            (int)m_player.getPosition().z / Chunk::SIZE};

        m_chunkMap.checkChunks();//This must be the last thing to happen in the update function here!
    }

    void Playing_State::draw (float dt, Master_Renderer& renderer)
    {
        m_chunkMap.draw(renderer);


        if (m_debugDisplayActive)
            Debug_Display::draw(renderer);

        renderer.processSfDrawable(crossHairSprite);
    }


    void Playing_State::exitState()
    {

        m_chunkMap.saveChunks();

        std::ofstream outFile ("Worlds/" + std::to_string(Noise::getSeed() ) + "/World_Info.data");
        outFile << (int)m_player.getPosition().x << " " << (int)m_player.getPosition().y << " " << (int)m_player.getPosition().z << std::endl;
    }

}

