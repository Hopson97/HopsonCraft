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
    sf::Clock gameTimer;

    auto MS_PER_UPDATE = 0.05; //20 Ticks/ updates per second

    float lastTime = gameTimer.getElapsedTime().asSeconds();
    float lag = 0.0f;
    while (Display::isOpen())
    {
        float current = gameTimer.getElapsedTime().asSeconds();
        float elapsed = current - lastTime;
        lastTime = current;
        lag += elapsed;

        sf::Event e;
        while (Display::get().pollEvent(e))
        {
            handleEvents(e);
        }
        if (!Display::isOpen() || m_states.empty())
        {
            break;
        }

        m_states.back()->input  (m_camera);

        //Fixed time-step of "MS_PER_UPDATE"
        while (lag >= MS_PER_UPDATE)
        {
            update(elapsed);
            lag -= MS_PER_UPDATE;
        }
        ///@TODO Are the the two update function calls able to be put in the fixed
        ///time step thing above?
        m_camera.update();
        m_states.back()->update(m_camera, elapsed);

        m_states.back()->draw(m_renderer);

        m_renderer.clear();
        m_renderer.update(m_camera);
    }
}

void Application::update(float elapsed)
{
    m_states.back()->fixedUpdate (m_camera, elapsed);
    #ifdef MUSIC_PLAYER_ACTIVE
    musicPlayer.update();
    #endif // MUSIC_PLAYER_ACTIVE
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

void Application::handleEvents(const sf::Event& e)
{
    if (e.type == sf::Event::Closed)
    {
        Display::close();
    }
    m_states.back()->input(e);
}

