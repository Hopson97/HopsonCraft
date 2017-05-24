#include "SMain_Menu.h"

#include "../Resource_Managers/Resource_Holder.h"

#include "../Application.h"
#include "SPlaying.h"

#include "../Util/Random.h"
#include "../Util/File_Util.h"

#include "../Display.h"

#include "SSettings_Menu.h"

namespace State
{
    Main_Menu::Main_Menu(Application& application)
    :   Game_State  (application)
    ,   m_frontMenu (GUI::Layout::Center)
    ,   m_playMenu  (GUI::Layout::Center)
    {
        auto backgrounds    = getFileNamesFromFolder("Data/Textures/Menu_BG");
        auto selection      = Random::intInRange(1, backgrounds.size());
        m_pMenuBackground   = &getResources().textures.get("Menu_BG/" + std::to_string(selection));

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
        m_frontMenu.addPadding(100);
        m_frontMenu.addBackgroud(*m_pMenuBackground);
        m_frontMenu.addComponent(std::make_unique<GUI::Image>("Logo", sf::Vector2f{800, 100}));

        m_frontMenu.addComponent(std::make_unique<GUI::Button>("Play", [&]()
        {
            m_pActiveMenu = &m_playMenu;
        }));

        m_frontMenu.addComponent(std::make_unique<GUI::Button>("Join (Unused)", [&]()
        { }));

        m_frontMenu.addComponent(std::make_unique<GUI::Button>("Settings", [&]()
        {
            m_application->pushState(std::make_unique<State::Settings_Menu>(*m_application, settings));
        }));

        m_frontMenu.addComponent(std::make_unique<GUI::Button>("Credits (Unused)", [&]()
        { }));

        m_frontMenu.addComponent(std::make_unique<GUI::Button>("Exit", [&]()
        {
            m_application->popState();
        }));

        //Play menu
        m_playMenu.addPadding(100);
        m_playMenu.addBackgroud(*m_pMenuBackground);
        m_playMenu.addComponent(std::make_unique<GUI::Image>("Logo", sf::Vector2f{800, 100}));

        m_playMenu.addComponent(std::make_unique<GUI::Toggle_Option_Button<std::string>>("Terrain Type",
        std::vector<std::pair<std::string, std::string>>
        {
            { "Classic", "Classic" },
            { "Islands", "Islands" },
        },
        settings.generator));

        m_playMenu.addComponent(std::make_unique<GUI::Toggle_Option_Button<bool>>("Super-flat Mode",
        std::vector<std::pair<std::string, bool>>
        {
            { "No",     false },
            { "Yes",    true  },
        },
        settings.isSuperFlat));

        m_playMenu.addComponent(std::make_unique<GUI::Button>("Play", [&]()
        {
            m_pActiveMenu = &m_frontMenu;
            settings.seed = Random::intInRange(0, 999'999);
            m_application->pushState(std::make_unique<State::Playing>(*m_application, settings));
        }));

        m_playMenu.addComponent(std::make_unique<GUI::Button>("Back", [&]()
        {
            m_pActiveMenu = &m_frontMenu;
        }));
    }
}
