#include "MainMenu.h"

#include "../ResourceManagers/ResourceHolder.h"

#include "../Util/Random.h"
#include "../Util/FileUtil.h"
#include "../GUI/BasicButton.h"
#include "../Display.h"
#include "../Application.h"
#include "SettingsMenu.h"
#include "Playing.h"

namespace State
{
    MainMenu::MainMenu(Application& application)
    :   Base  (application)
    {
        initMenu();
    }

    void MainMenu::input( const sf::Event& e)
    {
        m_pActiveMenu->input(e);
    }

    void MainMenu::input(Camera& camera)
    { }

    void MainMenu::fixedUpdate(Camera& camera, float dt)
    {
        m_pActiveMenu->update();
    }

    void MainMenu::draw(Renderer::Master& renderer)
    {
        m_pActiveMenu->draw(renderer);
    }

    void MainMenu::onOpen()
    {
        //Display::get().setFramerateLimit(30);
        m_application->getCamera().unhookEntity();
    }

    void MainMenu::initMenu()
    {
        //Front menu
        m_frontMenu.addComponent(std::make_unique<GUI::BasicButton>("Play", [&]()
        {
            m_pActiveMenu = &m_playMenu;
        }));

        m_frontMenu.addComponent(std::make_unique<GUI::BasicButton>("Settings", [&]()
        {
            m_application->pushState(std::make_unique<State::SettingsMenu>(*m_application, settings));
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
