#include "SPlaying.h"

#include <SFML/System/Clock.hpp>
#include <iostream>

#include "../World/Block/Block_Database.h"
#include "../Renderer/RMaster.h"
#include "../Camera.h"
#include "../Application.h"
#include "../Display.h"
#include "../Physics/Ray.h"

void Frame_Time_Checker::update()
{
    m_frameCount++;

    if (m_updateTimer.getElapsedTime().asSeconds() >= 0.3)
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
    Playing::Playing(Application& application,
                     const World_Settings& settings)
    :   Game_State  (application)
    ,   m_world     (settings)
    ,   m_player    (application.getCamera())
    ,   m_pauseMenu (GUI::Layout::Center)
    {
        application.getCamera().hookEntity(m_player);
        initHUD();
        initPause();

        m_quady.position = getCenterPosition();

        m_player.position = getCenterPosition();

        Display::get().setFramerateLimit(1000);
    }

    void Playing::input(const sf::Event& e)
    {

        if (m_isPaused)
        {
            m_pauseMenu.input(e);
            Display::get().setMouseCursorVisible(true);
        }
        else
        {
            Display::get().setMouseCursorVisible(false);
        }

        switch(e.type)
        {
            case sf::Event::KeyPressed:
                if (e.key.code == sf::Keyboard::Escape)
                {
                    m_isPaused = !m_isPaused;
                }
            default:
                break;
        }
    }

    void Playing::input(Camera& camera)
    {
        if (m_isPaused)
        {
            return;
        }

        m_player.input();


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        {
            m_player.position = getCenterPosition();
        }

        Ray raycast (m_player.rotation.y + 90,
                     m_player.rotation.x,
                     m_player.position);
        Vector3 lastPosition = raycast.getEndPoint();

        static sf::Clock timer;

        for (uint32_t i = 0; i < 5 / 0.1; i++)
        {
            raycast.step(0.1);

            if (raycast.getEndPoint().x < 0 ||
                raycast.getEndPoint().z < 0 ||
                raycast.getEndPoint().y < 1 ) return;

            CBlock block = m_world.getBlock(raycast.getEndPoint());

            if (!(block == Block::ID::Air ||
                  block == Block::ID::Water))
            {
                constexpr static float delay = 0.15f;

                if (timer.getElapsedTime().asSeconds() > delay)
                {
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        timer.restart();
                        m_world.setBlock(raycast.getEndPoint(), Block::ID::Air);
                        break;
                    }
                    else if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
                    {
                        timer.restart();
                        m_world.setBlock(lastPosition, Block::ID::Grass);
                        break;
                    }
                }
            }
            lastPosition = raycast.getEndPoint();
        }
    }


    void Playing::update(Camera& camera, float dt)
    {
        static sf::Clock c;
        m_quady.position.x += sin(c.getElapsedTime().asSeconds() / 5) * dt * 20;
        m_quady.position.z += cos(c.getElapsedTime().asSeconds() / 5) * dt * 20;
        m_quady.position.y = m_world.getHeightAt({m_quady.position.x,
                                                 0,
                                                 m_quady.position.z}) + 1;
        if (m_isPaused)
        {
            m_pauseMenu.update();
        }
        m_player.update(dt);
        m_world.checkPlayerBounds(m_player);

        ///@TODO Work out why this causes a crash for some odd reason.
        //m_world.updateChunks();

        m_frameTimeChecker.update();
    }

    void Playing::draw(Renderer::Master& renderer)
    {
        if (m_isPaused)
        {
            m_pauseMenu.draw(renderer);
        }
        m_world.drawWorld(renderer, m_application->getCamera());
        renderer.draw(m_quady);

        m_hud.draw(renderer);
    }

    Vector3 Playing::getCenterPosition()
    {
        int32_t centre = (m_world.getWorldSettings().worldSize * CHUNK_SIZE) / 2;

        return
        {
            centre + 0.5,
            m_world.getHeightAt({centre, 0, centre}) + 3,
            centre + 0.5
        };
    }


    void Playing::initHUD()
    {
        auto yPos = 0;

        auto getYPosition = [&yPos]()
        {
            float val = yPos;
            yPos += 27;
            return val;
        };

        m_hud.debug.addDebugSector("Seed: %.0f",    {0, getYPosition()},  &m_world.getWorldSettings().seed);

        m_hud.debug.addDebugSector("Frame Time: %fms",  {0, getYPosition()},  &m_frameTimeChecker.getFrameTime());
        m_hud.debug.addDebugSector("FPS: %.0f",         {0, getYPosition()},  &m_frameTimeChecker.getFPS());
        m_hud.debug.addDebugSector("Faces drawn: %.0f", {0, getYPosition()},  &m_world.m_facesDrawn);

        m_hud.debug.addDebugSector("Player Position: X: %.1f",  {0, getYPosition()},  &m_player.position.x);
        m_hud.debug.addDebugSector("Player Position: Y: %.1f",  {0, getYPosition()},  &m_player.position.y);
        m_hud.debug.addDebugSector("Player Position: Z: %.1f",  {0, getYPosition()},  &m_player.position.z);
    }

    void Playing::initPause()
    {
        m_pauseMenu.addComponent(std::make_unique<GUI::Image>("Logo", sf::Vector2f{800, 100}));
        m_pauseMenu.addPadding(200);
        m_pauseMenu.addComponent(std::make_unique<GUI::Button>("Resume", [&]()
        {
            m_isPaused = false;
        }));

        m_pauseMenu.addComponent(std::make_unique<GUI::Button>("Exit", [&]()
        {
            m_application->popState();
        }));
    }

}




