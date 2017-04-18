#include "SMain_Menu.h"

#include "../Resource_Managers/Resource_Holder.h"

#include "../Application.h"
#include "SPlaying.h"

namespace State
{
    Main_Menu::Main_Menu(Application& application)
    :   Game_State  (application)
    ,   m_frontMenu (GUI::Layout::Center)
    ,   m_playMenu  (GUI::Layout::Center)
    {
        initMenu();
    }

    void Main_Menu::input(sf::Event& e)
    {
        mp_activeMenu->input(e);
    }

    void Main_Menu::input(Camera& camera)
    { }

    void Main_Menu::update(Camera& camera, float dt)
    {
        mp_activeMenu->update();
    }

    void Main_Menu::draw(Renderer::Master& renderer)
    {
        mp_activeMenu->draw(renderer);
    }

    void Main_Menu::initMenu()
    {
        m_frontMenu.addPadding(100);
        m_frontMenu.addBackgroud(getResources().getTexture(Texture_ID::Menu_BG));
        m_frontMenu.addComponent(std::make_unique<GUI::Image>("Logo", sf::Vector2f{800, 100}));

        m_frontMenu.addComponent(std::make_unique<GUI::Button>("Play", [&]()
        {
            mp_activeMenu = &m_playMenu;
        }));

        mp_activeMenu->addComponent(std::make_unique<GUI::Button>("Join (Unused)", [&]()
        { }));

        mp_activeMenu->addComponent(std::make_unique<GUI::Button>("Settings (Unused)", [&]()
        { }));

        mp_activeMenu->addComponent(std::make_unique<GUI::Button>("Credits (Unused)", [&]()
        { }));

        m_frontMenu.addComponent(std::make_unique<GUI::Button>("Exit", [&]()
        {
            m_application->popState();
        }));

        //Play menu
        m_playMenu.addPadding(100);

        m_playMenu.addBackgroud(getResources().getTexture(Texture_ID::Menu_BG));

        m_playMenu.addComponent(std::make_unique<GUI::Image>("Logo", sf::Vector2f{800, 100}));

        m_playMenu.addComponent(std::make_unique<GUI::Toggle_Option_Button>("World Size",
        std::vector<std::string> { "Tiny", "Small", "Medium", "Large", "Huge"},
        std::vector<int32_t>     { 20,     32,       44,      56,      68},
        m_worldSize));

        m_playMenu.addComponent(std::make_unique<GUI::Button>("Play", [&]()
        {
            mp_activeMenu = &m_frontMenu;
            m_application->pushState(std::make_unique<State::Playing>(*m_application, m_worldSize));
        }));

        m_playMenu.addComponent(std::make_unique<GUI::Button>("Back", [&]()
        {
            mp_activeMenu = &m_frontMenu;
        }));


    }
}

/*
    m_application->pushState(std::make_unique<State::Playing>(*m_application));
*/
