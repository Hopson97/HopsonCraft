#include "Application.h"

#include <iostream>
#include <chrono>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>
#include "Resource_Managers/Resource_Holder.h"

#include "Display.h"

#include "States/SPlaying.h"

namespace
{
    sf::Text text;

    void checkFps (float f)
    {
        static sf::Clock timer;
        static sf::Clock printTimer;
        static auto numFrames = 0;

        numFrames++;

        if (printTimer.getElapsedTime().asSeconds() >= 1.0f)
        {
            text.setString(std::to_string(numFrames / timer.getElapsedTime().asSeconds()));
            printTimer.restart();
            numFrames = 0;
            timer.restart();
        }
    }
/*

    void checkFps (float frameTime)
    {
        static sf::Clock printTimer;
        if (printTimer.getElapsedTime().asSeconds() >= 0.5f)
        {
            text.setString(std::to_string(1/ frameTime));
            printTimer.restart();
        }
    }*/
}

Application::Application()
{
    text.setFont(getResources().getFont(Font_ID::RS));
    text.setOutlineThickness(1);
    text.setOutlineThickness(2);
    text.setCharacterSize(25);
    text.setString("Getting FPS...");
    pushState(std::make_unique<State::Playing>(*this));
}



void Application::runMainGameLoop()
{
    sf::Clock clock;

    while (Display::isOpen())
    {
        auto dt = clock.restart().asSeconds();

        m_renderer.clear();

        m_states.top()->input   (m_camera);

        m_states.top()->update  (m_camera, dt);

        m_states.top()->draw    (m_renderer);
        m_renderer.draw(text);
        m_renderer.update(m_camera);

        Display::checkForClose();

        checkFps (dt);
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

Camera& Application::getCamera()
{
    return m_camera;
}
