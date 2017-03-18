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
    ,   m_world     (application.getCamera(), m_hud)
    ,   m_player    (application.getCamera())
    ,   m_quady     (Block::Database::get().textures)
    {
        application.getCamera().hookEntity(m_player);
    }

    void Playing::input(Camera& camera)
    {

    }

    void Playing::update(Camera& camera, float dt)
    {
        m_quady.rotation.y += 10 * dt;

        m_player.input();
        m_player.update(dt);

    }

    void Playing::draw(Renderer::Master& renderer)
    {
        renderer.draw(m_quady);
        m_hud.draw(renderer);
    }
}
