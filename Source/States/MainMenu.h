#ifndef SMainMenu_H_INCLUDED
#define SMainMenu_H_INCLUDED

#include "Base.h"

#include "../GUI/Menu.h"

#include "../World/WorldSettings.h"

namespace State
{
    class MainMenu : public Base
    {
        public:
            MainMenu(Application& application);

            void input      (const sf::Event& e)        override;
            void input      (Camera& camera)            override;
            void update     (Camera& camera, float dt)  override{}
            void fixedUpdate(Camera& camera, float dt)  override;
            void draw       (Renderer::Master& renderer)override;

            void onOpen() override;

        private:
            void initMenu();

            GUI::Menu  m_frontMenu;
            GUI::Menu  m_playMenu;
            GUI::Menu* m_pActiveMenu = &m_frontMenu;

            int32_t m_worldSize = 0;
            int32_t m_noiseData = 0;

            WorldSettings settings;
    };
}

#endif // SMainMenu_H_INCLUDED
