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
    ,   m_quad      (Block::Database::get().textures)
    ,   m_world     (application.getCamera())
    {
        Block::Database::get().textures.bind();

        m_quad.position.z -= 2;
        m_quad.position.y -= 2;
    }

    void Playing::input(Camera& camera)
    {
        m_world.input(camera);
    }

    void Playing::update(Camera& camera, float dt)
    {
        camera.input(dt);
        m_world.update(dt);
    }

    void Playing::draw(Renderer::Master& renderer)
    {
        renderer.draw(m_quad);
        m_world.draw(renderer);
    }
}
