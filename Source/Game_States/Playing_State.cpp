#include "Playing_State.h"

#include <SFML/System/Clock.hpp>
#include <fstream>
#include <iostream>

#include "../World/Block/D_Blocks.h"
#include "../World/Block/Block_Type/Block_Type.h"
#include "../World/Block/Block_Enums.h"

#include "../Util/Directory_Creator.h"
#include "../Util/Debug_Display.h"
#include "../Util/Display.h"

#include "../Maths/Position_Converter_Maths.h"
#include "../Maths/General_Maths.h"
#include "../Maths/Ray.h"

#include "../Renderer/Master_Renderer.h"
#include "../Application.h"

#include "Menu_State.h"

#include "../World/World.h"

namespace State
{
    /**

    */
    Playing_State::Playing_State(Application& application,
                                const std::string& worldName,
                                uint32_t seed)
    :   Game_State      (application)
    ,   m_debugDisplay  ([&](){m_debugDisplayActive = !m_debugDisplayActive;}, sf::Keyboard::F3, sf::seconds(0.5))
    ,   m_worldName     (worldName)
    ,   m_worldSeed     (seed)
    {
        Display::hideMouse();
        Directory::create("Worlds");
        Directory::create("Worlds/" + m_worldName);

        loadWorldList();

        m_world = std::make_unique<World>(seed, worldName);
    }

    /**
        Input for SFML events
    */
    void Playing_State::input(const sf::Event& e)
    {
        m_debugDisplay.checkInput();
        m_world->input(e);
    }


    /**
        Real-Time input
    */
    void Playing_State::input ()
    {
        m_world->input();
    }

    /**
        Update the state
    */
    void Playing_State::update  (float dt, Camera& camera)
    {
        m_world->update(dt, camera);
    }


    /**

    */
    void Playing_State::draw (float dt, Master_Renderer& renderer)
    {
        m_world->draw(dt, renderer);

        tryAddPostFX(renderer);

        if (m_debugDisplayActive)
            Debug_Display::draw(renderer);

        m_world->drawXHair(renderer);
    }

    /*
        Sometimes, the player will be in such as place where there needs to be some kind of Post FX
        For exmaple:
            Player underwater -> Blur
    */
    void Playing_State::tryAddPostFX(Master_Renderer& renderer)
    {
        //UnderWater
        {
            //Get player position
            auto& wp    = m_world->getPlayer().position;
            auto bp     = Maths::worldToBlockPosition(wp);
            auto cp     = Maths::worldToChunkPosition(wp);

            const Chunk* chunk = m_world->getChunkMap().getChunkAt(cp);

            if (chunk)
            {
               //Player underwater
               if (chunk->getBlocks().getBlock(bp).getData().getID() == Block::ID::Water)
               {
                  // renderer.addPostFX(Post_FX::Blue);
                   renderer.addPostFX(Post_FX::Blur);
               }
            }
        }

        //Pause blur
        if (m_isPaused)
        {
            renderer.addPostFX(Post_FX::Blur);
        }
    }


    /**

    */
    void Playing_State::prepareExit(Master_Renderer& renderer)
    {
         //renderer.clear();
         //m_chunkMap->draw(renderer);
         //renderer.update(m_player.getCamera());
         //m_application->takeScreenshot("Worlds/" + m_worldName + "/thumbnail");
         m_application->changeState(std::make_unique<Main_Menu_State>(*m_application));
    }


    /**

    */
    void Playing_State::exitState()
    {
        save();
        Display::showMouse();
    }


    /**

    */
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


    /**

    */
    void Playing_State::save()
    {
        m_world->save();
        saveWorldList();
    }


    /**

    */
    void Playing_State::saveWorldList()
    {
        std::ofstream outFile ("Worlds/World_Names.txt");
        for (auto& world : m_worldFileNames)
        {
            outFile << world;
        }
    }


    /*
    void Playing_State::setUpPauseMenu()
    {
        m_pauseMenu.addPadding(150);
        m_pauseMenu.addComponent(std::make_unique<GUI::Button>("Resume", [&]()
        {
            m_state = PS_State::Play;
            Display::hideMouse();
        }));

        m_pauseMenu.addComponent(std::make_unique<GUI::Button>("Settings", [&]()
        {
            m_activeMenu = &m_settingsMenu;
        }));

        m_pauseMenu.addComponent(std::make_unique<GUI::Button>("Exit", [&]()
        {
            m_isExitGame = true;
        }));
    }

    void Playing_State::setUpSettingsMenu()
    {
        m_settingsMenu.addComponent(std::make_unique<GUI::Button>("Change Song", [&]()
        {
            m_application->resetSong();
        }));

        m_settingsMenu.addComponent(std::make_unique<GUI::Button>("Save", [&]()
        {
            save();
        }));

        m_settingsMenu.addComponent(std::make_unique<GUI::Button>("Back", [&]()
        {
            m_activeMenu = &m_pauseMenu;
        }));
    }
    */
}

