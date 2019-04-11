#ifndef SSettingsMenu_H_INCLUDED
#define SSettingsMenu_H_INCLUDED

#include "../ResourceManagers/ResourceHolder.h"

#include "Base.h"
#include "../GUI/Menu.h"

class WorldSettings;
class Application;

namespace State
{
    class SettingsMenu : public Base
    {
        public:
            SettingsMenu(Application& application, WorldSettings& settings);

            void input      (const sf::Event& e)        override;
            void input      (Camera& camera)            override;
            void update     (Camera& camera, float dt)  override{}
            void fixedUpdate(Camera& camera, float dt)  override;
            void draw       (Renderer::Master& renderer)override;

            void onOpen() override;

        private:
            void initMenu();

            WorldSettings* m_pWorldSettings;

            GUI::Menu m_frontMenu;
            GUI::Menu m_videoSettings;
            GUI::Menu* m_pActiveMenu   = &m_frontMenu;
    };
}

#endif // SSettingsMenu_H_INCLUDED
