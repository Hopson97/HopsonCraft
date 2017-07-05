#include "Playing.h"

#include <SFML/System/Clock.hpp>
#include <iostream>

#include "../World/Block/BlockDatabase.h"
#include "../Renderer/RMaster.h"
#include "../Camera.h"
#include "../Application.h"
#include "../Display.h"
#include "../Physics/Ray.h"
#include "../Input/FunctionToggleKey.h"
#include "SettingsMenu.h"

#include "../GUI/BasicButton.h"
#include "../GUI/Image.h"

namespace State
{
    Playing::Playing(Application& application,
                     const WorldSettings& settings)
    :   Base  (application)
    ,   m_world     (settings, application.getCamera())
    ,   m_player    (application.getCamera())
    ,   m_tickRate  ("Tick", "tps")
    ,   m_frameRate ("Frame", "fps")
    ,   m_pauseMenu (GUI::Layout::Center)
    {
        application.getCamera().hookEntity(m_player);
        initHUD();
        initPause();

        for (int x = 0; x < 5; x++)
        for (int z = 0; z < 5; z++)
        {
            Cube cube;
            cube.position = {x, -1, z};
            m_cubes.push_back(cube);
        }
        m_player.position   = getCenterPosition();

        Display::get().getRaw().setFramerateLimit(144);
    }

    void Playing::input(const sf::Event& e)
    {
        if (m_isPaused)
        {
            m_pauseMenu.input(e);
            Display::get().getRaw().setMouseCursorVisible(true);
        }
        else
        {
            Display::get().getRaw().setMouseCursorVisible(false);
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
        editBlockInput();
    }

    void Playing::update(Camera& camera, float dt)
    {
        m_player.doCollisionTest(m_world, dt);
        m_player.update(dt);
    }

    void Playing::fixedUpdate(Camera& camera, float dt)
    {
        if (m_isPaused)
        {
            m_pauseMenu.update();
        }
        m_tickRate.update();
    }

    void Playing::draw(Renderer::Master& renderer)
    {
        m_frameRate.update();
        if (m_isPaused)
        {
            m_pauseMenu.draw(renderer);
        }

        for (auto& cube : m_cubes)
            renderer.draw(cube);

        m_hud.draw(renderer);

        static Toggle drawDebugHUD(sf::Keyboard::Key::F3, sf::seconds(0.5));
        if (drawDebugHUD)
        {
            m_debugHud.draw(renderer);
        }
    }

    void Playing::onOpen()
    {

    }

    void Playing::editBlockInput()
    {

    }


    Vector3 Playing::getCenterPosition()
    {
        return
        {
            0, 1, 0
        };
    }


    void Playing::initHUD()
    {
        auto addSection = [&](std::string&& format, const float& f)
        {
            m_debugHud.addDebugSector(std::move(format), &f);
        };

        m_tickRate.registerForDebug (m_debugHud);
        m_frameRate.registerForDebug(m_debugHud);

        addSection("Faces drawn: %.0f", m_world.m_facesDrawn);

        addSection("Player Position: X: %.1f", m_player.position.x);
        addSection("Player Position: Y: %.1f", m_player.position.y);
        addSection("Player Position: Z: %.1f", m_player.position.z);
    }

    void Playing::initPause()
    {
        m_pauseMenu.addComponent(std::make_unique<GUI::Image>("Logo", sf::Vector2f{800, 100}));
        m_pauseMenu.addPadding(200);
        m_pauseMenu.addComponent(std::make_unique<GUI::BasicButton>("Resume", [&]()
        {
            m_isPaused = false;
        }));

        m_pauseMenu.addComponent(std::make_unique<GUI::BasicButton>("Settings", [&]()
        {
            m_application->pushState<State::SettingsMenu>(*m_application, m_world.m_worldSettings);
        }));

        m_pauseMenu.addComponent(std::make_unique<GUI::BasicButton>("Exit", [&]()
        {
            m_application->popState();
        }));
    }

}




