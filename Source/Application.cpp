#include "Application.h"

#include <iostream>
#include <chrono>
#include <thread>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>
#include "ResourceManagers/ResourceHolder.h"

#include "Display.h"

#include "States/StateMainMenu.h"

Application::Application()
{
    pushState<StateMainMenu>(*this);
}

void Application::runMainGameLoop()
{
    constexpr uint32_t  TICKS_PER_FRAME = 30;
    const sf::Time      MS_PER_TICK     = sf::seconds((float)1 / (float)TICKS_PER_FRAME);

    uint32_t tickCount = 0;

    sf::Clock timer;

    auto lastTime   = timer.getElapsedTime();
    auto tickLag    = sf::Time::Zero;

    auto& display = Display::get();

    while (display.isOpen())
    {
        if (m_states.empty()) break;
        auto& state         = currentState();
        auto currentTime    = timer.getElapsedTime();
        auto elapsed        = currentTime - lastTime;
        lastTime            = currentTime;
        tickLag             += elapsed;

        state.input (m_camera);

        while (tickLag >= MS_PER_TICK)
        {
            tickCount++;

            state.fixedUpdate (m_camera, elapsed.asSeconds());
            musicPlayer.update();

            tickLag -= MS_PER_TICK;
        }

        m_camera.update();
        state.update(m_camera, elapsed.asSeconds());

        state.draw(m_renderer);
        m_renderer.update(m_camera);
        handleEvents();

        if (m_shouldPop)
        {
            m_shouldPop = false;
            m_states.pop_back();
            if (!m_states.empty())
            {
                currentState().onOpen();
            }
        }
    }
}

void Application::handleEvents()
{
    static auto& display = Display::get().getRaw();
    sf::Event e;

    while (display.pollEvent(e))
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

void Application::popState()
{
    m_shouldPop = true;
}

StateBase& Application::currentState()
{
    return *m_states.back();
}

Camera& Application::getCamera()
{
    return m_camera;
}

