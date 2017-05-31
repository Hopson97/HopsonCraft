#include "SMain_Menu.h"

#include "../Resource_Managers/Resource_Holder.h"

#include "../Application.h"
#include "SPlaying.h"

#include "../Util/Random.h"
#include "../Util/File_Util.h"

#include "../Display.h"

#include "SSettings_Menu.h"

#include "../GUI/BasicButton.h"

namespace State
{
    Main_Menu::Main_Menu(Application& application)
    :   Game_State  (application)
    {
        initMenu();
    }

    void Main_Menu::input( const sf::Event& e)
    {
        m_pActiveMenu->input(e);
    }

    void Main_Menu::input(Camera& camera)
    { }

    void Main_Menu::fixedUpdate(Camera& camera, float dt)
    {
        m_pActiveMenu->update();
    }

    void Main_Menu::draw(Renderer::Master& renderer)
    {
        m_pActiveMenu->draw(renderer);
    }

    void Main_Menu::onOpen()
    {
        //Display::get().setFramerateLimit(30);
        m_application->getCamera().unhookEntity();
    }

    void Main_Menu::initMenu()
    {
        //Front menu
        m_frontMenu.addComponent(std::make_unique<GUI::BasicButton>("Play", [&]()
        {
            m_pActiveMenu = &m_playMenu;
        }));

        m_frontMenu.addComponent(std::make_unique<GUI::BasicButton>("Settings", [&]()
        {
            m_application->pushState(std::make_unique<State::Settings_Menu>(*m_application, settings));
        }));

        m_frontMenu.addComponent(std::make_unique<GUI::BasicButton>("Credits (Unused)", [&]()
        { }));

        m_frontMenu.addComponent(std::make_unique<GUI::BasicButton>("Exit", [&]()
        {
            m_application->popState();
        }));

        //Play menu
        m_playMenu.addComponent(std::make_unique<GUI::BasicButton>("Play", [&]()
        {
            m_pActiveMenu = &m_frontMenu;
            settings.seed = Random::intInRange(0, 999'999);
            m_application->pushState(std::make_unique<State::Playing>(*m_application, settings));
        }));

        m_playMenu.addComponent(std::make_unique<GUI::BasicButton>("Back", [&]()
        {
            m_pActiveMenu = &m_frontMenu;
        }));
    }
}
