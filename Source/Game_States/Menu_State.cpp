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
    ,   m_menu      (GUI::Layout::Center)
    {
        m_menu.addComponent(std::make_unique<GUI::Image>("logo"));

        m_menu.addComponent(std::make_unique<GUI::Button>("Play", [&]()
                            {
                                m_application->changeState (std::make_unique<Playing_State>(
                                                            *m_application,
                                                            *m_worldName,
                                                            *m_seed));
                            }));

        m_menu.addBackgroud("bg");

        Display::showMouse();

        m_seed = new int(5000);
        m_worldName = new std::string("Test");
    }

    Main_Menu_State::~Main_Menu_State()
    {
        delete m_seed;
        delete m_worldName;
    }


    void Main_Menu_State::input(const sf::Event& e)
    {
        m_menu.input(e);
    }

    void Main_Menu_State::input()
    {

    }

    void Main_Menu_State::update(float dt, Camera& camera)
    {
        m_menu.update();
    }

    void Main_Menu_State::draw(float dt, Master_Renderer& renderer)
    {
        m_menu.draw(renderer);
    }

    void Main_Menu_State::exitState()
    {
        delete m_seed;
        delete m_worldName;
    }

}
