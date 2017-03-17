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
    ,   m_worldFile ("Test")
    ,   m_world     (application.getCamera(), m_hud, m_worldFile)
    ,   m_player    (application.getCamera())
    ,   m_quady     (Block::Database::get().textures)
    {
        application.getCamera().hookEntity(m_player);

        m_quady.position.y = 1;

        for (int x = 0; x < 25; x++)
        {
            for (int z = 0; z < 25; z++)
            {
                m_quads.emplace_back((Block::Database::get().textures));
                m_quads.back().position = {x, 0, z};

            }
        }
    }

    void Playing::input(Camera& camera)
    {
        m_player.input();
        //m_world.input(camera);
    }

    void Playing::update(Camera& camera, float dt)
    {
        //m_world.update(dt);
        m_player.update(dt);

        m_application->getCamera().update();
    }

    void Playing::draw(Renderer::Master& renderer)
    {
        //m_world     .draw(renderer);
        for (auto& quad : m_quads)
        {
            renderer.draw(quad);
        }
        renderer.draw(m_quady);


        m_hud.draw(renderer);
    }
}
