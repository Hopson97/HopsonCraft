#include "Application.h"

#include <iostream>

#include "Display.h"

#include "States/SPlaying.h"

namespace
{
    void checkFps ()
    {
        static sf::Clock timer;
        static sf::Clock printTimer;
        static auto numFrames = 0;

        numFrames++;

        if (printTimer.getElapsedTime().asSeconds() >= 1.0f)
        {
            auto fps = (float)numFrames / timer.getElapsedTime().asSeconds();
            printTimer.restart();
            std::cout << fps << std::endl;

            numFrames = 0;
            timer.restart();
        }
    }

}

Application::Application()
{
    pushState(std::make_unique<State::Playing>(*this));
    camera.position.y = World_Constants::CH_SIZE;
    camera.position.x = World_Constants::CH_SIZE / 2;
    camera.position.z = World_Constants::CH_SIZE / 2;
}

void Application::runMainGameLoop()
{
    sf::Clock clock;

    while (Display::isOpen())
    {
        checkFps ();
        auto dt = clock.restart().asSeconds();

        m_renderer.clear();

        m_states.top()->input   (camera);
        m_states.top()->update  (camera, dt);
        m_states.top()->draw    (m_renderer);

        m_renderer.update(camera);
        Display::checkForClose();
    }
}

void Application::pushState(std::unique_ptr<State::Game_State> state)
{
    m_states.push(std::move(state));
}

void Application::popState()
{
    m_states.pop();
}
