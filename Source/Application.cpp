#include "Application.h"

#include <iostream>
#include <chrono>
#include <thread>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>
#include "ResourceManagers/ResourceHolder.h"

#include "Display.h"

#include "States/MainMenu.h"

Application::Application()
{
    pushState<State::MainMenu>(*this);
}

void Application::runMainGameLoop()
{
    unsigned ticks = 0;

    constexpr float TICKS_PER_SECOND = 20;
    const sf::Time MS_PER_UPDATE = sf::seconds(1.0f/ TICKS_PER_SECOND);
    sf::Clock gameTimer;

    auto lastTime = gameTimer.getElapsedTime();
    auto updateLag = sf::Time::Zero;
    while (Display::get().isOpen() && !m_states.empty())
    {
        auto current = gameTimer.getElapsedTime();
        auto elapsed = current - lastTime;
        lastTime = current;
        updateLag += elapsed;

        handleEvents();
        if (!Display::get().isOpen() || m_states.empty())
            break;

        currentState().input  (m_camera);

        while (updateLag >= MS_PER_UPDATE)
        {
            ticks++;
            update(elapsed.asSeconds());
            updateLag -= MS_PER_UPDATE;
        }

        m_camera.update();
        currentState().update(m_camera, elapsed.asSeconds());

        render();
    }
}

void Application::handleEvents()
{
    sf::Event e;
    while (Display::get().getRaw().pollEvent(e))
    {
        if (e.type == sf::Event::Closed)
        {
            Display::get().close();
        }
        currentState().input(e);
    }
}

void Application::update(float elapsed)
{
    currentState().fixedUpdate (m_camera, elapsed);
    musicPlayer.update();

    currentState().update(m_camera, elapsed);
}

void Application::render()
{
    m_renderer.clear();
    currentState().draw(m_renderer);
    m_renderer.update(m_camera);
}

void Application::popState()
{
    m_states.pop_back();
    if (!m_states.empty())
    {
        currentState().onOpen();
    }
}

State::Base& Application::currentState()
{
    return *m_states.back();
}



Camera& Application::getCamera()
{
    return m_camera;
}

