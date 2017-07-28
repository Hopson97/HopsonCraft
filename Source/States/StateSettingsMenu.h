#ifndef SSettingsMenu_H_INCLUDED
#define SSettingsMenu_H_INCLUDED

#include "../ResourceManagers/ResourceHolder.h"

#include "StateBase.h"
#include "../GUI/Menu.h"

class Application;

class StateSettingsMenu : public StateBase
{
    public:
        StateSettingsMenu(Application& application);

        void input      (const sf::Event& e)        override;
        void input      (Camera& camera)            override;
        void update     (Camera& camera, float dt)  override{}
        void fixedUpdate(Camera& camera, float dt)  override;
        void draw       (MasterRenderer& renderer)override;

        void onOpen() override;

    private:
        void initMenu();

        GUI::Menu m_frontMenu;
        GUI::Menu m_videoSettings;
        GUI::Menu m_audioSettings;
        GUI::Menu m_controlSettings;

        GUI::Menu* m_pActiveMenu   = &m_frontMenu;
};

#endif // SSettingsMenu_H_INCLUDED
