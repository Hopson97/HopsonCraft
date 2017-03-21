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
        m_fps = m_frameCount / m_timer.getElapsedTime().asMilliseconds();
        if (m_fps > 0)
        {
            m_frameTime = 1.0f / m_fps;
        }
        m_fps *= 1000;
        m_frameCount = 0;
        m_updateTimer.restart();
        m_timer.restart();
    }
}

const float& Frame_Time_Checker::getFrameTime()
{
    return m_frameTime;
}

const float& Frame_Time_Checker::getFPS()
{
    return m_fps;
}



namespace State
{
    namespace
    {
        uint32_t worldSize = 16;
    }

    Playing::Playing(Application& application)
    :   Game_State  (application)
    ,   m_world     (application.getCamera(), worldSize)
    ,   m_player    (application.getCamera())
    ,   m_quady     (Block::Database::get().textures)
    {
        application.getCamera().hookEntity(m_player);
        initHUD();

        m_player.position =
        {
            (worldSize * CHUNK_SIZE) / 2,
            CHUNK_SIZE + 5 * 17,
            (worldSize * CHUNK_SIZE) / 2
        };
    }

    void Playing::input(sf::Event& e)
    {

    }

    void Playing::input(Camera& camera)
    {
        m_player.input();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        {
            m_player.position =
            {
                (worldSize * CHUNK_SIZE) / 2,
                CHUNK_SIZE + 5 * 17,
                (worldSize * CHUNK_SIZE) / 2
            };
        }
    }

    void Playing::update(Camera& camera, float dt)
    {
        m_player.update(dt);
        m_world.checkPlayerBounds(m_player);
        m_frameTimeChecker.update();
    }

    void Playing::draw(Renderer::Master& renderer)
    {

        m_world.drawWorld(renderer, m_application->getCamera());
        renderer.draw(m_quady);
        m_hud.draw(renderer);
    }

    void Playing::initHUD()
    {
        float yPos = 0;

        auto getYPosition = [&yPos]()
        {
            float val = yPos;
            yPos += 27;
            return val;
        };

        m_hud.debug.addDebugSector("Frame Time: %fms",          {0,  getYPosition()},  &m_frameTimeChecker.getFrameTime());
        m_hud.debug.addDebugSector("FPS: %.0f",                 {0,  getYPosition()},  &m_frameTimeChecker.getFPS());
        m_hud.debug.addDebugSector("Player Position: X: %.1f",  {0, getYPosition()},  &m_player.position.x);
        m_hud.debug.addDebugSector("Player Position: Y: %.1f",  {0, getYPosition()},  &m_player.position.y);
        m_hud.debug.addDebugSector("Player Position: Z: %.1f",  {0, getYPosition()},  &m_player.position.z);
    }
}




