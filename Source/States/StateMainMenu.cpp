#include "StateMainMenu.h"

#include "../ResourceManagers/ResourceHolder.h"

#include "../Util/Random.h"
#include "../Util/FileUtil.h"
#include "../GUI/BasicButton.h"
#include "../Display.h"
#include "../Application.h"
#include "StateSettingsMenu.h"
#include "StatePlaying.h"

StateMainMenu::StateMainMenu(Application& application)
:   StateBase  (application)
{
    initMenu();
}

void StateMainMenu::input( const sf::Event& e)
{
    m_pActiveMenu->input(e);
}

void StateMainMenu::input(Camera& camera)
{ }

void StateMainMenu::fixedUpdate(Camera& camera, float dt)
{
    m_pActiveMenu->update();
}

void StateMainMenu::draw(MasterRenderer& renderer)
{
    m_pActiveMenu->draw(renderer);
}

void StateMainMenu::onOpen()
{
    Display::get().getRaw().setFramerateLimit(30);
    m_application->getCamera().unhookEntity();
}

void StateMainMenu::initMenu()
{
    //Front menu
    m_frontMenu.addComponent(std::make_unique<GUI::BasicButton>("Play", [&]()
    {
        m_pActiveMenu = &m_playMenu;
    }));

    m_frontMenu.addComponent(std::make_unique<GUI::BasicButton>("Settings", [&]()
    {
        m_application->pushState<StateSettingsMenu>(*m_application);
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
        m_application->pushState<StatePlaying>(*m_application);
    }));

    m_playMenu.addComponent(std::make_unique<GUI::BasicButton>("Back", [&]()
    {
        m_pActiveMenu = &m_frontMenu;
    }));
}

