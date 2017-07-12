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
    constexpr uint32_t  TICKS_PER_FRAME = 30;
    const sf::Time      MS_PER_TICK     = sf::seconds((float)1 / (float)TICKS_PER_FRAME);

    uint32_t tickCount = 0;

    sf::Clock timer;

    auto lastTime   = timer.getElapsedTime();
    auto tickLag    = sf::Time::Zero;

    while (Display::get().isOpen())
    {
        auto currentTime    = timer.getElapsedTime();
        auto elapsed        = currentTime - lastTime;
        lastTime            = currentTime;
        tickLag             += elapsed;

        handleEvents();
        if ( m_states.empty() ||
            !Display::get().isOpen())
        {
            break;
        }
        currentState().input (m_camera);

        while (tickLag >= MS_PER_TICK)
        {
            tickCount++;
            update(elapsed.asSeconds());
            tickLag -= MS_PER_TICK;
        }

        m_camera.update();
        currentState().update(m_camera, elapsed.asSeconds());

        m_renderer.clear();
        currentState().draw(m_renderer);
        m_renderer.update(m_camera);
    }
}

void Application::handleEvents()
{
    sf::Event e;
    while (Display::get().getRaw().pollEvent(e))
    {
        currentState().input(e);
        switch(e.type)
        {
            case sf::Event::Closed:
                Display::get().close();
                break;

            default:
                break;
        }

    }
}

void Application::update(float elapsed)
{
    currentState().fixedUpdate (m_camera, elapsed);
    musicPlayer.update();

    currentState().update(m_camera, elapsed);
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

