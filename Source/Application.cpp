#include "Application.h"

#include <iostream>
#include <chrono>
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

    /**
        @TODO
        In real Minecraft, the game updates every 0.05s
        Aka, 20 Ticks Per Second.
        Problem is of course this makes the game feel very
        stutter-like.
        So, we have to figure out how to make this work
        better using interpolation and other
        techniques.
    */
    auto MS_PER_UPDATE = 0.0083; //120 TPS

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

        while (lag >= MS_PER_UPDATE)
        {
            update(elapsed);
            lag -= MS_PER_UPDATE;
        }
        m_states.back()->draw   (m_renderer);

        m_renderer.clear();
        m_renderer.update(m_camera);


    }
}

void Application::update(float elapsed)
{
    m_states.back()->update (m_camera, elapsed);
    m_camera.update();
    m_musicPlayer.update();
}

void Application::pushState(std::unique_ptr<State::Game_State> state)
{
    state->onOpen();
    m_states.push_back(std::move(state));
}

void Application::popState()
{
   m_states.pop_back();
   m_camera.unhookEntity();
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


/*
namespace
{
    struct Timestep
    {
        public:
            Timestep(float initialTime)
            : m_timestep(0.0f), m_lastTime(initialTime)
            {
            }

            void update(float currentTime)
            {
                m_timestep = currentTime - m_lastTime;
                m_lastTime = currentTime;
            }

            float asSeconds() const { return asMillis() * 0.001f; }
            float asMillis() const { return m_timestep; }

        private:
            float m_timestep;
            float m_lastTime;
    };
}


void Application::runMainGameLoop()
{
    sf::Clock   gameTimer;
    Timestep    timeStep    (gameTimer.getElapsedTime().asMilliseconds());

    auto timer          = 0.0f;
    auto updateTimer    = (float)gameTimer.getElapsedTime().asMilliseconds();

    uint64_t updates = 0;
    uint64_t frames  = 0;

    constexpr auto UPDATE_TIME = 1000.0f / 60.0f;    //in ms

    while (Display::isOpen())
    {
        if (m_states.empty()) break;

        sf::Event e;
        while (Display::get().pollEvent(e))
        {
            handleEvents(e);
        }
        if (!Display::isOpen()) break;

        auto now = (float)gameTimer.getElapsedTime().asMilliseconds();

        //if (now - updateTimer > UPDATE_TIME)
        {
            timeStep.update(now);
            ++updates;
            updateTimer += UPDATE_TIME;
            m_states.back()->input  (m_camera);
            m_states.back()->update (m_camera, timeStep.asSeconds());
            m_camera.update();
        }

        frames++;
        sf::Clock frameTime;

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
*/
