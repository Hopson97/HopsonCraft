#include "Application.h"

#include <iostream>
#include <chrono>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>
#include "Resource_Managers/Resource_Holder.h"

#include "Display.h"

#include "States/SPlaying.h"
#include "States/SMain_Menu.h"

Application::Application()
{
    pushState(std::make_unique<State::Main_Menu>(*this));
}

void Application::runMainGameLoop()
{
    sf::Clock gameTimer;

    while (Display::isOpen())
    {
        if (m_states.empty())
            break;

        auto elapsed = gameTimer.restart().asSeconds();

        m_musicPlayer.update();

        sf::Event e;
        while (Display::get().pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
            {
                Display::close();
            }
            m_states.back()->input(e);
        }
        if (!Display::isOpen())
        {
            break;
        }

        m_states.back()->input  (m_camera);
        m_states.back()->update (m_camera, elapsed);
        m_camera.update();
        m_states.back()->draw   (m_renderer);

        m_renderer.clear();
        m_renderer.update(m_camera);
        if (m_shouldPopState)
        {
            realPopState();
            m_shouldPopState = false;
        }
    }
}

void Application::pushState(std::unique_ptr<State::Game_State> state)
{
    m_states.push_back(std::move(state));
}

void Application::popState()
{
   m_shouldPopState = true;
}

Camera& Application::getCamera()
{
    return m_camera;
}

void Application::realPopState()
{
     m_states.pop_back();
}
