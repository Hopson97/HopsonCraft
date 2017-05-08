#include "SMain_Menu.h"

#include "../Resource_Managers/Resource_Holder.h"

#include "../Application.h"
#include "SPlaying.h"

#include "../Util/Random.h"
#include "../Util/File_Util.h"

#include "../Display.h"

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

        settings.name = "Test";

        initMenu();
    }

    void Main_Menu::input( const sf::Event& e)
    {
        mp_activeMenu->input(e);
    }

    void Main_Menu::input(Camera& camera)
    { }

    void Main_Menu::fixedUpdate(Camera& camera, float dt)
    {
        mp_activeMenu->update();
    }

    void Main_Menu::draw(Renderer::Master& renderer)
    {
        mp_activeMenu->draw(renderer);
    }

    void Main_Menu::onOpen()
    {
        Display::get().setFramerateLimit(30);
    }

    void Main_Menu::initMenu()
    {
        m_frontMenu.addPadding(100);
        m_frontMenu.addBackgroud(*m_pMenuBackground);
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
        m_playMenu.addBackgroud(*m_pMenuBackground);
        m_playMenu.addComponent(std::make_unique<GUI::Image>("Logo", sf::Vector2f{800, 100}));

        m_playMenu.addComponent(std::make_unique<GUI::Toggle_Option_Button>("World Size",
        std::vector<std::string> { "Developer Mode", "Tiny", "Small", "Medium", "Large", "Huge \n Warning: Potentially high memory usage and low FPS!"},
        std::vector<int32_t>     {  12,             20,     32,       44,      56,      68},
        settings.worldSize));

        m_playMenu.addComponent(std::make_unique<GUI::Toggle_Option_Button>("Terrain Type",
        std::vector<std::string> { "Smooth", "Normal", "Mountains", "Water"},
        std::vector<int32_t>     { 0,         1,           2,       3},
        m_noiseData));

        m_playMenu.addComponent(std::make_unique<GUI::Toggle_Option_Button>("Infinite Terrain",
        std::vector<std::string> { "No", "Yes"  },
        std::vector<int32_t>     {  0,    1     },
        settings.infiniteTerrain));

        m_playMenu.addComponent(std::make_unique<GUI::Button>("Play", [&]()
        {
            mp_activeMenu = &m_frontMenu;

            switch(m_noiseData)
            {
                case 0:
                    settings.noiseData = {4, WATER_LEVEL, 0.4, 500};
                    break;

                case 1:
                    //settings.noiseData = {7, 76, 0.51, 235, -18};
                    settings.noiseData = {7, 85, 0.51, 235, -15};
                    break;

                case 2:
                    //seeds:
                    //92879 - VERY TALL MOUTAIN
                    //5184
                    //72390 - Very cool valleys
                    settings.noiseData = {8, 550, 0.50, 283, -395};
                    break;

                case 3:
                    settings.noiseData = {7, 43, 0.5, 55};
                    break;
            }

            settings.seed = Random::intInRange(0, 99'999);

            m_application->pushState(std::make_unique<State::Playing>(*m_application, settings));
        }));

        m_playMenu.addComponent(std::make_unique<GUI::Button>("Back", [&]()
        {
            mp_activeMenu = &m_frontMenu;
        }));
    }
}
