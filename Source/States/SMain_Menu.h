#ifndef SMAIN_MENU_H_INCLUDED
#define SMAIN_MENU_H_INCLUDED

#include "Game_State.h"

#include "../GUI/Menu.h"

#include "../World/World_Settings.h"

namespace State
{
    class Main_Menu : public Game_State
    {
        public:
            Main_Menu(Application& application);

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

            World_Settings settings;
    };
}

#endif // SMAIN_MENU_H_INCLUDED
