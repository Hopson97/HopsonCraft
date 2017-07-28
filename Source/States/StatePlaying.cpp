#include "StatePlaying.h"

#include <SFML/System/Clock.hpp>
#include <iostream>

#include "../Camera.h"
#include "../Application.h"
#include "../Display.h"

#include "../Renderer/MasterRenderer.h"

#include "../Input/FunctionToggleKey.h"


#include "../GUI/BasicButton.h"
#include "../GUI/Image.h"

#include "StateSettingsMenu.h"

StatePlaying::StatePlaying(Application& application)
:   StateBase   (application)
,   m_world     (application.getCamera())
,   m_player    (application.getCamera())
,   m_tickRate  ("Tick", "TPS")
,   m_frameRate ("Frame", "FPS")
,   m_pauseMenu (GUI::Layout::Center)
{
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

void StatePlaying::input(const sf::Event& e)
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

void StatePlaying::input(Camera& camera)
{
    if (m_isPaused) return;

    m_player.input();
}

void StatePlaying::update(Camera& camera, float dt)
{
    m_player.doCollisionTest(m_world, dt);
    m_player.update(dt);
}

void StatePlaying::fixedUpdate(Camera& camera, float dt)
{
    pauseUpdate(camera, dt);
    m_tickRate.update();
}

void StatePlaying::draw(MasterRenderer& renderer)
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

void StatePlaying::onOpen()
{
    Display::get().getRaw().setFramerateLimit(144);
}

void StatePlaying::pauseInput(const sf::Event& e)
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

void StatePlaying::pauseUpdate(Camera& camera, float dt)
{
    if (!m_isPaused)
        return;

    m_pauseMenu.update();
}

void StatePlaying::pauseRender(MasterRenderer& renderer)
{
    if (!m_isPaused)
        return;

    m_pauseMenu.draw(renderer);
}



void StatePlaying::initHUD()
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

void StatePlaying::initPause()
{
    m_pauseMenu.addComponent(std::make_unique<GUI::Image>("Logo", sf::Vector2f{800, 100}));
    m_pauseMenu.addPadding(200);
    m_pauseMenu.addComponent(std::make_unique<GUI::BasicButton>("Resume", [&]()
    {
        m_isPaused = false;
    }));

    m_pauseMenu.addComponent(std::make_unique<GUI::BasicButton>("Settings", [&]()
    {
        m_application->pushState<StateSettingsMenu>(*m_application);
    }));

    m_pauseMenu.addComponent(std::make_unique<GUI::BasicButton>("Exit", [&]()
    {
        m_application->popState();
    }));
}




