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

#include "../Texture/CubeTexture.h"

Texture::CubeTexture t;

namespace State
{
    Playing::Playing(Application& application)
    :   Base        (application)
    ,   m_world     (application.getCamera())
    ,   m_player    (application.getCamera())
    ,   m_tickRate  ("Tick", "TPS")
    ,   m_frameRate ("Frame", "FPS")
    ,   m_pauseMenu (GUI::Layout::Center)
    {
        t.loadFromFile(
        {
            "Data/Textures/Skybox/Test/right.png",
            "Data/Textures/Skybox/Test/left.png",
            "Data/Textures/Skybox/Test/top.png",
            "Data/Textures/Skybox/Test/bottom.png",
            "Data/Textures/Skybox/Test/back.png",
            "Data/Textures/Skybox/Test/front.png"
        });

        application.getCamera().hookEntity(m_player);
        initHUD();
        initPause();

        constexpr int cubeCount = 3;
        for (int x = -cubeCount; x < cubeCount; x++)
        for (int z = -cubeCount; z < cubeCount; z++)
        {
            Cube cube;
            cube.position = {x, -1, z};
            m_cubes.push_back(cube);
        }
        m_player.position   = {0, 2, 0};
    }

    void Playing::input(const sf::Event& e)
    {
        pauseInput(e);

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
        if (m_isPaused) return;

        m_player.input();
    }

    void Playing::update(Camera& camera, float dt)
    {
        m_player.doCollisionTest(m_world, dt);
        m_player.update(dt);
    }

    void Playing::fixedUpdate(Camera& camera, float dt)
    {
        pauseUpdate(camera, dt);
        m_tickRate.update();
    }

    void Playing::draw(Renderer::Master& renderer)
    {
        pauseRender(renderer);

        static Toggle drawDebugHUD(sf::Keyboard::Key::F3, sf::seconds(0.5));
        m_frameRate.update();


        for (auto& cube : m_cubes)
            renderer.draw(cube);

        m_hud.draw(renderer);

        if (drawDebugHUD)
        {
            m_debugHud.draw(renderer);
        }
    }

    void Playing::onOpen()
    {
        Display::get().getRaw().setFramerateLimit(144);
    }

    void Playing::pauseInput(const sf::Event& e)
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
    }

    void Playing::pauseUpdate(Camera& camera, float dt)
    {
        if (!m_isPaused)
            return;

        m_pauseMenu.update();
    }

    void Playing::pauseRender(Renderer::Master& renderer)
    {
        if (!m_isPaused)
            return;

        m_pauseMenu.draw(renderer);
    }



    void Playing::initHUD()
    {
        auto addSection = [&](std::string&& format, const float& f)
        {
            m_debugHud.addDebugSector(std::move(format), &f);
        };

        m_tickRate  .registerForDebug   (m_debugHud);
        m_frameRate .registerForDebug   (m_debugHud);

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
            m_application->pushState<State::SettingsMenu>(*m_application);
        }));

        m_pauseMenu.addComponent(std::make_unique<GUI::BasicButton>("Exit", [&]()
        {
            m_application->popState();
        }));
    }

}




