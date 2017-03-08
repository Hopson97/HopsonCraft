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
    ,   m_world     (application.getCamera(), m_player)
    ,   m_player    (application.getCamera())
    { }

    void Playing::input(Camera& camera)
    {
        m_player.input();
        m_world.input(camera);
    }

    void Playing::update(Camera& camera, float dt)
    {
        m_world.update(dt);
    }

    void Playing::draw(Renderer::Master& renderer)
    {
        m_world     .draw(renderer);
        m_vignette  .draw(renderer);
        m_crosshair .draw(renderer);
    }
}
