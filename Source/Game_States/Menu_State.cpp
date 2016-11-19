#include "Menu_State.h"

#include "../GUI/Button.h"
#include "../Application.h"
#include "../Util/Display.h"
#include "Playing_State.h"

namespace State
{
    Main_Menu_State::Main_Menu_State(Application& application)
    :   Game_State  (application)
    {
        m_menu.addComponent(std::make_unique<GUI::Button>("Play", [&]()
                            {
                                m_application->pushState (std::make_unique<Playing_State>(
                                                      *m_application,
                                                      "Test",
                                                       99999));
                            }));
        Display::showMouse();
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

    }

}
