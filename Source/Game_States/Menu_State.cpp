#include "Menu_State.h"

#include <fstream>
#include <iostream>

#include "../Util/Display.h"
#include "../Application.h"
#include "../GUI/GUI.h"
#include "Playing_State.h"

namespace State
{
    Main_Menu_State::Main_Menu_State(Application& application)
    :   Game_State  (application)
//    ,   m_frontMenu     (GUI::Layout::Center)
  //  ,   m_newGameMenu   (GUI::Layout::Center)
   // ,   m_loadmenu      (GUI::Layout::Center)
    {
        m_background.loadFromFile("Data/Images/bg.png");
        Display::showMouse();

        initFrontMenu();
        initNewGameMenu();

       // m_activeMenu = &m_frontMenu;
    }

    void Main_Menu_State::input(const sf::Event& e)
    {
       // m_activeMenu->input(e);
    }

    void Main_Menu_State::input()
    { }

    void Main_Menu_State::update(float dt, Camera& camera)
    {
       // m_activeMenu->update();

        if (m_makeWorld)
        {
            m_application->changeState (std::make_unique<Playing_State>(
                                        *m_application,
                                        m_worldName,
                                        getSeed()));
        }
    }

    void Main_Menu_State::draw(float dt, Master_Renderer& renderer)
    {
        //m_activeMenu->draw(renderer);
    }

    void Main_Menu_State::exitState()
    { }

    uint32_t Main_Menu_State::getSeed()
    {
        std::string newString;
        for(auto& ch : m_seedString)
        {
            if (isalpha(ch))
            {
                int x = ch;
                newString += std::to_string(x);
            }
            else
            {
                newString += ch;
            }
        }

        while (newString.length() > 8) newString.pop_back();

        return std::stoi(newString);
    }



    void Main_Menu_State::initFrontMenu()
    {/*
        m_frontMenu.addBackgroud(m_background);
        m_frontMenu.addComponent(std::make_unique<GUI::Image>("Data/Images/logo", sf::Vector2f{800, 250}));

        m_frontMenu.addComponent(std::make_unique<GUI::Button>("New Game", [&]()
        {
            m_activeMenu = &m_newGameMenu;
        }));
        m_frontMenu.addComponent(std::make_unique<GUI::Button>("Load Game", [&]()
        {
            genLoadMenu();
            m_activeMenu = &m_loadmenu;
        }));

        m_frontMenu.addComponent(std::make_unique<GUI::Button>("Exit Game", [&]()
        {
            Display::close();
        }));*/
    }


    void Main_Menu_State::initNewGameMenu()
    {/*
        m_newGameMenu.addPadding(150);
        m_newGameMenu.addBackgroud(m_background);
        m_newGameMenu.addComponent(std::make_unique<GUI::Text_Box>(15, sf::Vector2f{500, 100}, "World Name", m_worldName));
        m_newGameMenu.addComponent(std::make_unique<GUI::Text_Box>(8, sf::Vector2f{500, 100}, "Seed", m_seedString));

        m_newGameMenu.addComponent(std::make_unique<GUI::Button>("Create", [&]()
        {
            if (m_seedString.length() > 0 && m_worldName.length() > 0)
                m_makeWorld = true;
        }));

        m_newGameMenu.addComponent(std::make_unique<GUI::Button>("Back", [&]()
        {
            m_activeMenu = &m_frontMenu;
            m_seedString.clear();
            m_worldName.clear();
        }));*/
    }

    void Main_Menu_State::genLoadMenu()
    {/*
        m_worldFileNames.clear();
        m_loadmenu.clear();
        m_loadmenu.addPadding(150);
        m_loadmenu.addBackgroud(m_background);
        m_worldSeeds.clear();

        std::ifstream worldsFile("Worlds/World_Names.txt");
        std::string line;
        while (std::getline(worldsFile, line))
        {
            m_worldFileNames.push_back(line);
        }

        for (auto& world : m_worldFileNames)
        {
            std::fstream inFile("Worlds/" + world + "/World_Info.data");
            std::string line;
            int seed;
            while(std::getline(inFile, line))
            {
                if(line == "seed")
                {
                    inFile >> seed;
                    break;
                }
            }

            m_worldSeeds.insert(std::make_pair(&world, seed));

            m_loadmenu.addComponent(std::make_unique<GUI::Imaged_Button>("Worlds/" + world + "/thumbnail", world,[&]()
            {
                m_worldName = world;
                m_seedString = std::to_string(m_worldSeeds.at(&world));
                m_makeWorld = true;
            }));
            inFile.close();
        }



        m_loadmenu.addComponent(std::make_unique<GUI::Button>("Back", [&]()
        {
            m_activeMenu = &m_frontMenu;
        }));*/
    }

}
