#include "StateSettingsMenu.h"

#include "../ResourceManagers/ResourceHolder.h"

#include "../Application.h"
#include "StatePlaying.h"

#include "../GUI/BasicButton.h"

StateSettingsMenu::StateSettingsMenu(Application& application)
:   StateBase   (application)
{
    initMenu();
}

void StateSettingsMenu::input(const sf::Event& e)
{
    m_pActiveMenu->input(e);
}

void StateSettingsMenu::input(Camera& camera)
{ }

void StateSettingsMenu::fixedUpdate(Camera& camera, float dt)
{
    m_pActiveMenu->update();
}

void StateSettingsMenu::draw(MasterRenderer& renderer)
{
    m_pActiveMenu->draw(renderer);
}

void StateSettingsMenu::onOpen()
{ }

void StateSettingsMenu::initMenu()
{
    //Front menu
    m_frontMenu.addComponent(std::make_unique<GUI::BasicButton>("Video Settings", [&]()
    {
        m_pActiveMenu = &m_videoSettings;
    }));

    m_frontMenu.addComponent(std::make_unique<GUI::BasicButton>("Audio Settings", [&]()
    {
        m_pActiveMenu = &m_audioSettings;
    }));

    m_frontMenu.addComponent(std::make_unique<GUI::BasicButton>("Control Settings", [&]()
    {
        m_pActiveMenu = &m_controlSettings;
    }));

    m_frontMenu.addComponent(std::make_unique<GUI::BasicButton>("Back", [&]()
    {
        m_application->popState();
    }));

    //Video settings menu
    m_videoSettings.addComponent(std::make_unique<GUI::BasicButton>("Back", [&]()
    {
        m_pActiveMenu = &m_frontMenu;
    }));

    //Audio settings menu
    m_audioSettings.addComponent(std::make_unique<GUI::BasicButton>("Back", [&]()
    {
        m_pActiveMenu = &m_frontMenu;
    }));

    //Control settings menu
    m_controlSettings.addComponent(std::make_unique<GUI::BasicButton>("Back", [&]()
    {
        m_pActiveMenu = &m_frontMenu;
    }));
}

