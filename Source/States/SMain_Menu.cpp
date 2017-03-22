#include "SMain_Menu.h"

#include "../Resource_Managers/Resource_Holder.h"

#include "../Application.h"
#include "SPlaying.h"

namespace State
{
    Main_Menu::Main_Menu(Application& application)
    :   Game_State  (application)
    ,   m_menu      (GUI::Layout::Center)
    {
        initMenu();
    }

    void Main_Menu::input(sf::Event& e)
    {
        m_menu.input(e);
    }

    void Main_Menu::input(Camera& camera)
    { }

    void Main_Menu::update(Camera& camera, float dt)
    {
        m_menu.update();
    }

    void Main_Menu::draw(Renderer::Master& renderer)
    {
        m_menu.draw(renderer);
    }

    void Main_Menu::initMenu()
    {
        m_menu.addPadding(100);
        m_menu.addBackgroud(getResources().getTexture(Texture_ID::Menu_BG));
        m_menu.addComponent(std::make_unique<GUI::Image>("Logo", sf::Vector2f{500, 50}));

        m_menu.addComponent(std::make_unique<GUI::Button>("Play", [&]()
        {
            m_application->pushState(std::make_unique<State::Playing>(*m_application));
        }));

        m_menu.addComponent(std::make_unique<GUI::Button>("Exit", [&]()
        {
            m_application->popState();
        }));
    }

}
