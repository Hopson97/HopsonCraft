#include "playing_state.h"

#include <SFML/System/Clock.hpp>
#include <fstream>
#include <iostream>

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

#include "Button.h"

#include "../Application.h"

#include "Menu_State.h"

#include "../Util/Time.h"

namespace State
{
    Playing_State::Playing_State(Application& application,
                                const std::string& worldName,
                                uint32_t seed)
    :   Game_State          (application)
    ,   m_playerPosition    (Maths::worldToChunkPosition(m_player.getPosition()))
    ,   m_debugDisplay      ([&](){m_debugDisplayActive = !m_debugDisplayActive;}, sf::Keyboard::F3, sf::seconds(0.5))
    ,   m_worldName         (worldName)
    ,   m_worldSeed         (seed)
    ,   m_pauseMenu         (GUI::Layout::Center)
    ,   m_settingsMenu      (GUI::Layout::Center)
    {

        Display::hideMouse();
        Directory::create("Worlds");
        Directory::create("Worlds/" + m_worldName);

        loadWorldFile();
        loadWorldList();

        setUpPauseMenu();
        setUpSettingsMenu();

        crossHairTexture.loadFromFile("Data/Images/Crosshair.png");
        crossHairSprite.setTexture(crossHairTexture);
        crossHairSprite.setPosition(Display::get().getSize().x / 2 - crossHairSprite.getTexture()->getSize().x / 2,
                                    Display::get().getSize().y / 2 - crossHairSprite.getTexture()->getSize().y / 2);


        m_chunkMap = std::make_unique<Chunk_Map>(m_playerPosition, worldName, m_worldSeed);
    }

    void Playing_State::input(const sf::Event& e)
    {
        static sf::Clock c;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && c.getElapsedTime().asSeconds() > 0.1)
        {
            switch (m_state)
            {
                case State_t::Play:
                    m_state = State_t::Pause;
                    m_activeMenu = &m_pauseMenu;
                    Display::showMouse();
                    break;

                case State_t::Pause:
                    m_state = State_t::Play;
                    Display::hideMouse();
                    break;

            }
            c.restart().asSeconds();
        }

        if (m_state == State_t::Play)
        {
            m_chunkMap->input(e);
            m_player.toggleInput(e);
            m_debugDisplay.checkInput(e);
        }
        else if (m_state == State_t::Pause)
        {
            m_activeMenu->input(e);
        }
    }


    void Playing_State::input ()
    {
        static sf::Clock blockEditClock;

        if (m_state == State_t::Play)
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Mouse::isButtonPressed(sf::Mouse::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::P))
            {
                if (blockEditClock.getElapsedTime().asSeconds() > 0.2)
                {
                    blockEdit();
                    blockEditClock.restart();
                }
            }

            m_player.input();
        }
    }

    void Playing_State::blockEdit()
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

            auto* block       = &m_chunkMap->getBlockAt(ray.getEndPoint());
            //auto worldPoint   = Maths::worldToBlockPosition(ray.getEndPoint());
            //auto playerPoint  = Maths::worldToBlockPosition(m_player.getPosition());

            if (block->getPhysicalState() == Block::Physical_State::Solid ||
                block->getPhysicalState() == Block::Physical_State::Flora)
            {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                   //if (worldPoint != playerPoint)
                        m_chunkMap->setBlock(Block::air, ray.getEndPoint());
                }
                else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
                {
                    //if (worldPoint != playerPoint)
                        m_chunkMap->setBlock(m_player.getHeldBlock(), oldRayEnd);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
                {
                    //if (worldPoint != playerPoint)
                        m_chunkMap->makeExplosion(ray.getEndPoint(), 8);
                }
                break;
            }
            else
            {
                oldRayEnd = ray.getEndPoint();
            }
        }
    }

    void Playing_State::update  (float dt, Camera& camera)
    {
        if (m_state == State_t::Play)
        {
            m_player.update(dt, camera);
            m_chunkMap->checkChunks();//This must be the last thing to happen in the update function here!
            m_playerPosition = {(int)m_player.getPosition().x / Chunk::SIZE,
                                (int)m_player.getPosition().z / Chunk::SIZE};
            Debug_Display::addPlayerPosition(m_player.getPosition());
        }
        else if (m_state == State_t::Pause)
        {
            m_activeMenu->update();
        }
    }

    void Playing_State::draw (float dt, Master_Renderer& renderer)
    {
        //Draw the chunks
        m_chunkMap->draw(renderer);

        tryAddPostFX(renderer);

        if (m_state == State_t::Play)
        {
            if (m_debugDisplayActive)   Debug_Display::draw(renderer);
            renderer.draw(crossHairSprite);
        }
        else if (m_state == State_t::Pause)
            m_activeMenu->draw(renderer);


        if(exitGame)
            prepareExit(renderer);
    }

    void Playing_State::tryAddPostFX(Master_Renderer& renderer)
    {
        //Get player position
        auto wp = m_player.getPosition();
        auto bp = Maths::worldToBlockPosition(wp);
        auto cp = Maths::worldToChunkPosition(wp);

        if (m_chunkMap->getChunkAt(cp))
        {
           //Player underwater
           if (m_chunkMap->getChunkAt(cp)->getBlocks().getBlock(bp).getID() == Block::ID::Water)
           {
               renderer.addPostFX(Post_FX::Blue);
           }
        }
    }

    void Playing_State::prepareExit(Master_Renderer& renderer)
    {
            renderer.clear();
            m_chunkMap->draw(renderer);
            renderer.update(m_player.getCamera());
            m_application->changeState(std::make_unique<Main_Menu_State>(*m_application));
    }



    void Playing_State::exitState()
    {
        m_chunkMap->saveChunks();

        saveWorldFile();
        saveWorldList();

        Display::showMouse();
        m_application->takeScreenshot("Worlds/" + m_worldName + "/thumbnail.png");
    }


    void Playing_State::loadWorldFile()
    {
        std::ifstream inFile("Worlds/" + m_worldName + "/World_Info.data");
        std::string line;
        if (std::getline(inFile, line))
        {
            if (line == "pos")
            {
                int x, y, z;
                inFile >> x >> y >> z;
                m_player.setPosition({x + 0.5,
                                      y,            //Offset by 0.5 as the exact numbers put the player on a block corner
                                      z + 0.5});
            }
        }
    }

    void Playing_State::loadWorldList()
    {
        m_worldFileNames.push_back(m_worldName + "\n");

        std::ifstream inFile("Worlds/World_Names.txt");
        std::string line;
        while (std::getline(inFile, line))
        {
            if (line == m_worldName)    //Avoid getting multiple copies of a world
                continue;
            else
                m_worldFileNames.push_back(line + "\n");
        }
    }


    void Playing_State::saveWorldFile()
    {
        std::ofstream outFile ("Worlds/" + m_worldName + "/World_Info.data");
        outFile << "pos\n" << (int)m_player.getPosition().x << " " << (int)m_player.getPosition().y << " " << (int)m_player.getPosition().z << std::endl;
        outFile << "seed\n" << m_worldSeed << std::endl;
        outFile << "time\n" << Time::getTimeString() << std::endl;
        outFile << "date\n" << Time::getDateString() << std::endl;
    }

    void Playing_State::saveWorldList()
    {
        std::ofstream outFile ("Worlds/World_Names.txt");
        for (auto& world : m_worldFileNames)
        {
            outFile << world;
        }
    }


    void Playing_State::setUpPauseMenu()
    {
        m_pauseMenu.addPadding(150);
        m_pauseMenu.addComponent(std::make_unique<GUI::Button>("Resume", [&]()
        {
            m_state = State_t::Play;
            Display::hideMouse();
        }));

        m_pauseMenu.addComponent(std::make_unique<GUI::Button>("Settings", [&]()
        {
            m_activeMenu = &m_settingsMenu;
        }));

        m_pauseMenu.addComponent(std::make_unique<GUI::Button>("Exit", [&]()
        {
            exitGame = true;
        }));
    }

    void Playing_State::setUpSettingsMenu()
    {
        m_settingsMenu.addComponent(std::make_unique<GUI::Button>("Back", [&]()
        {
            m_activeMenu = &m_pauseMenu;
        }));
    }


}

