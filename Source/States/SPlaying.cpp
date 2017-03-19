#include "SPlaying.h"

#include <SFML/System/Clock.hpp>
#include <iostream>

#include "../World/Block/Block_Database.h"
#include "../Renderer/RMaster.h"
#include "../Camera.h"
#include "../Application.h"

void Frame_Time_Checker::update()
{
    m_frameCount++;

    if (m_updateTimer.getElapsedTime().asSeconds() >= 0.5)
    {
        float fps = m_frameCount / m_timer.getElapsedTime().asMilliseconds();
        if (fps > 0)
        {
            m_frameTime = 1.0f / fps;
        }
        m_frameCount = 0;
        m_updateTimer.restart();
        m_timer.restart();
    }
}

const float& Frame_Time_Checker::getFrameTime()
{
    return m_frameTime;
}


namespace State
{
    sf::Clock clock;

    Playing::Playing(Application& application)
    :   Game_State  (application)
    ,   m_world     (application.getCamera())
    ,   m_player    (application.getCamera())
    ,   m_quady     (Block::Database::get().textures)
    {
        application.getCamera().hookEntity(m_player);

        float yPos = 0;
        m_hud.debug.addDebugSector("Frame Time: %fms",        {0,     yPos},  &m_frameTimeChecker.getFrameTime());
        yPos += 27;
        m_hud.debug.addDebugSector("Player Position: X: %.1f",  {0,     yPos},  &m_player.position.x);
        m_hud.debug.addDebugSector("Y: %.1f",                   {170,   yPos},  &m_player.position.y);
        m_hud.debug.addDebugSector("Z: %.1f",                   {220,   yPos},  &m_player.position.z);

        for (int32_t x = 0 ; x < 10 ; x++)
        {
            for (int32_t z = 0; z < 10; z++)
            {
                m_chunkSection.push_back(std::make_unique<Chunk::Section>(Chunk::Chunklet_Position(x, 0, z)));
            }
        }
    }

    void Playing::input(Camera& camera)
    {
        m_player.input();
    }

    void Playing::update(Camera& camera, float dt)
    {
        m_quady.rotation.y += 10 * dt;


        m_player.update(dt);
        m_frameTimeChecker.update();
    }

    void Playing::draw(Renderer::Master& renderer)
    {
        renderer.draw(m_quady);
        for (auto& c : m_chunkSection)
        {
             renderer.draw(*c);
        }

        m_hud.draw(renderer);
    }
}
