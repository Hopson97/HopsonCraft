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
    pushState(std::make_unique<State::MainMenu>(*this));
}

void Application::runMainGameLoop()
{
    unsigned ticks = 0;

    const sf::Time MS_PER_UPDATE = sf::seconds(0.05);//20 Ticks/ updates per second
    sf::Clock gameTimer;

    auto lastTime = gameTimer.getElapsedTime();
    auto updateLag = sf::Time::Zero;
    while (getDisplay().isOpen() || !m_states.empty())
    {
        auto current = gameTimer.getElapsedTime();
        auto elapsed = current - lastTime;
        lastTime = current;
        updateLag += elapsed;

        handleEvents();
        if (!getDisplay().isOpen() || m_states.empty())
            break;

        m_states.back()->input  (m_camera);

        while (updateLag >= MS_PER_UPDATE)
        {
            ticks++;
            update(elapsed.asSeconds());
            updateLag -= MS_PER_UPDATE;
        }

        m_camera.update();
        m_states.back()->update(m_camera, elapsed.asSeconds());

        render();
    }
}

void Application::handleEvents()
{
    sf::Event e;
    while (getDisplay().get().pollEvent(e))
    {
        if (e.type == sf::Event::Closed)
        {
            getDisplay().close();
        }
        m_states.back()->input(e);
    }
}

void Application::update(float elapsed)
{
    m_states.back()->fixedUpdate (m_camera, elapsed);
    musicPlayer.update();

    m_camera.update();
    m_states.back()->update(m_camera, elapsed);
}

void Application::render()
{
    m_renderer.clear();
    m_states.back()->draw(m_renderer);
    m_renderer.update(m_camera);
}


void Application::pushState(std::unique_ptr<State::Base> state)
{
    state->onOpen();
    m_states.push_back(std::move(state));
}

void Application::popState()
{
    m_states.pop_back();
    if (!m_states.empty())
    {
        m_states.back()->onOpen();
    }
}

Camera& Application::getCamera()
{
    return m_camera;
}

