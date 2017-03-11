#include "SPlaying.h"

#include <SFML/System/Clock.hpp>

#include "../World/Block/Block_Database.h"
#include "../Renderer/RMaster.h"
#include "../Camera.h"
#include "../Application.h"

namespace State
{
    sf::Clock clock;

    Playing::Playing(Application& application)
    :   Game_State  (application)
    ,   m_world     (application.getCamera(), m_player, m_hud)
    ,   m_player    (application.getCamera())
    {
        application.getCamera().hookEntity(m_player);
    }

    void Playing::input(Camera& camera)
    {
        m_player.input();
        m_world.input(camera);
    }

    void Playing::update(Camera& camera, float dt)
    {
        m_world.update(dt);

        m_application->getCamera().update();
    }

    void Playing::draw(Renderer::Master& renderer)
    {
        m_world     .draw(renderer);

        m_hud.draw(renderer);
    }
}
