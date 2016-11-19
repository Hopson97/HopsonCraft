#include "Menu_State.h"

#include "../GUI/Button.h"
#include "../GUI/Image.h"

#include "../Application.h"

#include "../Util/Display.h"

#include "Playing_State.h"

namespace State
{
    Main_Menu_State::Main_Menu_State(Application& application)
    :   Game_State  (application)
    ,   m_frontMenu      (GUI::Layout::Center)
    {
        m_frontMenu.addComponent(std::make_unique<GUI::Image>("logo", sf::Vector2f{800, 250}));

        m_frontMenu.addComponent(std::make_unique<GUI::Button>("Play", [&]()
                            {
                                m_application->changeState (std::make_unique<Playing_State>(
                                                            *m_application,
                                                            *m_worldName,
                                                            *m_seed));
                            }));

        m_frontMenu.addBackgroud("bg");

        Display::showMouse();

        m_seed = new int(5000);
        m_worldName = new std::string("Test");

        m_activeMenu = &m_frontMenu;
    }

    Main_Menu_State::~Main_Menu_State()
    {
        delete m_seed;
        delete m_worldName;
    }


    void Main_Menu_State::input(const sf::Event& e)
    {
        m_activeMenu->input(e);
    }

    void Main_Menu_State::input()
    {

    }

    void Main_Menu_State::update(float dt, Camera& camera)
    {
        m_activeMenu->update();
    }

    void Main_Menu_State::draw(float dt, Master_Renderer& renderer)
    {
        m_activeMenu->draw(renderer);
    }

    void Main_Menu_State::exitState()
    {
        delete m_seed;
        delete m_worldName;
    }

}
