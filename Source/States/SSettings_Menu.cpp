#include "SSettings_Menu.h"

#include "../Resource_Managers/Resource_Holder.h"

#include "../Application.h"
#include "SPlaying.h"

namespace State
{
    Settings_Menu::Settings_Menu(Application& application, World_Settings& settings)
    :   Game_State          (application)
    ,   m_pWorldSettings    (&settings)
    ,   m_frontMenu         (GUI::Layout::Center)
    ,   m_videoSettings     (GUI::Layout::Center)
    {

    }

    void Settings_Menu::input(const sf::Event& e)
    {

    }

    void Settings_Menu::input(Camera& camera)
    {
    }

    void Settings_Menu::fixedUpdate(Camera& camera, float dt)
    {

    }

    void Settings_Menu::draw(Renderer::Master& renderer)
    {

    }

    void Settings_Menu::onOpen()
    {

    }
}
