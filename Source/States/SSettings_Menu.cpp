#include "SSettings_Menu.h"

#include "../Resource_Managers/Resource_Holder.h"

#include "../Application.h"
#include "SPlaying.h"

#include "../Util/File_Util.h"

namespace State
{
    Settings_Menu::Settings_Menu(Application& application, World_Settings& settings)
    :   Game_State          (application)
    ,   m_pWorldSettings    (&settings)
    ,   m_frontMenu         (GUI::Layout::Center)
    ,   m_videoSettings     (GUI::Layout::Center)
    {
        auto backgrounds    = getFileNamesFromFolder("Data/Textures/Menu_BG");
        auto selection      = Random::intInRange(1, backgrounds.size());
        m_pMenuBackground   = &getResources().textures.get("Menu_BG/" + std::to_string(selection));

        initMenu();
    }

    void Settings_Menu::input(const sf::Event& e)
    {
        m_pActiveMenu->input(e);
    }

    void Settings_Menu::input(Camera& camera)
    { }

    void Settings_Menu::fixedUpdate(Camera& camera, float dt)
    {
        m_pActiveMenu->update();
    }

    void Settings_Menu::draw(Renderer::Master& renderer)
    {
        m_pActiveMenu->draw(renderer);
    }

    void Settings_Menu::onOpen()
    { }

    void Settings_Menu::initMenu()
    {
        //Front menu
        m_frontMenu.addPadding(100);
        m_frontMenu.addBackgroud(*m_pMenuBackground);
        m_frontMenu.addComponent(std::make_unique<GUI::Image>("Logo", sf::Vector2f{800, 100}));

        m_frontMenu.addComponent(std::make_unique<GUI::Button>("Video Settings", [&]()
        {
            m_pActiveMenu = &m_videoSettings;
        }));

        m_frontMenu.addComponent(std::make_unique<GUI::Button>("Back", [&]()
        {
            m_application->popState();
        }));

        //Video settings menu
        m_videoSettings.addPadding(100);
        m_videoSettings.addBackgroud(*m_pMenuBackground);
        m_videoSettings.addComponent(std::make_unique<GUI::Image>("Logo", sf::Vector2f{800, 100}));

        m_videoSettings.addComponent(std::make_unique<GUI::Toggle_Option_Button<int32_t>>("Render Distance",
        std::vector<std::pair<std::string, int32_t>>
        {
            { "Very Tiny, 5",   10 },
            { "Tiny, 10",       20 },
            { "Small, 16",      32 },
            { "Medium, 22",     44 },
            { "Large, 28",      56 },
            { "Huge, 34",       68 },
        },
        m_pWorldSettings->renderDistance));

        m_videoSettings.addComponent(std::make_unique<GUI::Button>("Back", [&]()
        {
            m_pActiveMenu = &m_frontMenu;
        }));
    }
}
