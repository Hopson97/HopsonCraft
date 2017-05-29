#include "Application.h"

#include <iostream>
#include <chrono>
#include <thread>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>
#include "Resource_Managers/Resource_Holder.h"

#include "Display.h"

#include "States/SMain_Menu.h"

Application::Application()
{
    pushState(std::make_unique<State::Main_Menu>(*this));
}

void Application::runMainGameLoop()
{
    constexpr double MS_PER_UPDATE = 0.05;//20 Ticks/ updates per second
    sf::Clock gameTimer;

    float lastTime = gameTimer.getElapsedTime().asSeconds();
    float lag = 0.0f;
    while (Display::isOpen() || !m_states.empty())
    {
        float current = gameTimer.getElapsedTime().asSeconds();
        float elapsed = current - lastTime;
        lastTime = current;
        lag += elapsed;


        handleEvents();
        if (!Display::isOpen() || m_states.empty()) break;

        m_states.back()->input  (m_camera);

        while (lag >= MS_PER_UPDATE)
        {
            update(elapsed);
            lag -= MS_PER_UPDATE;
        }

        m_camera.update();
        m_states.back()->update(m_camera, elapsed);

        render();
    }
}


void Application::handleEvents()
{
    sf::Event e;
    while (Display::get().pollEvent(e))
    {
        if (e.type == sf::Event::Closed)
        {
            Display::close();
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


void Application::pushState(std::unique_ptr<State::Game_State> state)
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

