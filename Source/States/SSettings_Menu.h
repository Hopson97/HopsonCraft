#ifndef SSETTINGS_MENU_H_INCLUDED
#define SSETTINGS_MENU_H_INCLUDED

#include "../Resource_Managers/Resource_Holder.h"

#include "Game_State.h"
#include "../GUI/GUI.h"

class World_Settings;
class Application;

namespace sf
{
    class Texture;
}

namespace State
{
    class Settings_Menu : public Game_State
    {
        public:
            Settings_Menu(Application& application, World_Settings& settings);

            void input      (const sf::Event& e)        override;
            void input      (Camera& camera)            override;
            void update     (Camera& camera, float dt)  override{}
            void fixedUpdate(Camera& camera, float dt)  override;
            void draw       (Renderer::Master& renderer)override;

            void onOpen() override;

        private:
            void initMenu();

            World_Settings* m_pWorldSettings;

            GUI::Panel m_frontMenu;
            GUI::Panel m_videoSettings;
            GUI::Panel* m_pActiveMenu   = &m_frontMenu;

            const sf::Texture* m_pMenuBackground;
    };
}

#endif // SSETTINGS_MENU_H_INCLUDED
