#ifndef SMAIN_MENU_H_INCLUDED
#define SMAIN_MENU_H_INCLUDED

#include "Game_State.h"

#include "../GUI/GUI.h"

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

            GUI::Panel  m_frontMenu;
            GUI::Panel  m_playMenu;
            GUI::Panel* m_pActiveMenu = &m_frontMenu;

            int32_t m_worldSize = 0;
            int32_t m_noiseData = 0;

            const sf::Texture* m_pMenuBackground;

            World_Settings settings;
    };
}

#endif // SMAIN_MENU_H_INCLUDED
