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

        m_quady.position.y = 1;

        for (int x = 0; x < 10; x++)
        {
            for (int z = 0; z < 10; z++)
            {
                m_quads.emplace_back((Block::Database::get().textures));
                m_quads.back().position = {x * 2 + 1, 0, z * 2 + 1};

            }
        }
    }

    void Playing::input(Camera& camera)
    {

    }

    void Playing::update(Camera& camera, float dt)
    {
        m_application->getCamera().update();
        m_player.input();
        m_player.update(dt);

    }

    void Playing::draw(Renderer::Master& renderer)
    {

        for (auto& quad : m_quads)
        {
            renderer.draw(quad);
        }


        renderer.draw(m_quady);


        m_hud.draw(renderer);
    }
}
