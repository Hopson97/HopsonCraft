#include "Menu_State.h"

#include "../GUI/Button.h"
#include "../GUI/Image.h"
#include "../GUI/Text_Box.h"

#include "../Application.h"

#include "../Util/Display.h"

#include "Playing_State.h"

namespace State
{
    Main_Menu_State::Main_Menu_State(Application& application)
    :   Game_State  (application)
    ,   m_frontMenu     (GUI::Layout::Center)
    ,   m_newGameMenu   (GUI::Layout::Center)
    {
        m_background.loadFromFile("Data/Images/bg.png");
        Display::showMouse();

        initFrontMenu();
        initNewGameMenu();

        m_activeMenu = &m_frontMenu;
    }

    void Main_Menu_State::input(const sf::Event& e)
    {
        m_activeMenu->input(e);
    }

    void Main_Menu_State::input()
    { }

    void Main_Menu_State::update(float dt, Camera& camera)
    {
        m_activeMenu->update();

        if (m_makeWorld)
        {
            m_application->changeState (std::make_unique<Playing_State>(
                                        *m_application,
                                        m_worldName,
                                        std::stoi(m_seedString)));
        }
    }

    void Main_Menu_State::draw(float dt, Master_Renderer& renderer)
    {
        m_activeMenu->draw(renderer);
    }

    void Main_Menu_State::exitState()
    { }


    void Main_Menu_State::initFrontMenu()
    {
        m_frontMenu.addBackgroud(m_background);
        m_frontMenu.addComponent(std::make_unique<GUI::Image>("logo", sf::Vector2f{800, 250}));

        m_frontMenu.addComponent(std::make_unique<GUI::Button>("New Game", [&]()
        {
            m_activeMenu = &m_newGameMenu;
        }));
        m_frontMenu.addComponent(std::make_unique<GUI::Button>("Load Game", [&]()
        {
            //m_makeWorld = true;
        }));

        m_frontMenu.addComponent(std::make_unique<GUI::Button>("Exit Game", [&]()
        {
            Display::close();
        }));
    }


    void Main_Menu_State::initNewGameMenu()
    {
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
        }));
    }
}
