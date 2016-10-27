#include "Application.h"

#include "Display.h"
#include "OpenGL/GLEW/glew.h"

#include <cstdlib>
#include <iostream>
#include <string>

#include "Debug_Display.h"
#include "Game_States/Playing_State.h"

namespace
{
    void checkFps ();
}

Application::Application()
{
    srand(time(nullptr));
    std::cout << "Starting app!" << std::endl;
    m_stateStack.push(std::make_unique<State::Playing_State>(*this));
}


void Application::runMainLoop()
{
    sf::Clock dtClock;

    while (Display::isOpen())
    {
        auto dt = dtClock.restart().asSeconds();
        Display::clear();

        m_stateStack.top()->input   (dt);
        m_stateStack.top()->update  (dt);
        m_stateStack.top()->draw    (dt);

        Display::prepareSfDraw();
        checkFps();
        m_stateStack.top()->sfDraw  (dt);
        Display::endSfDraw();

        Display::update();
        Display::checkForClose();
    }
}


void Application::pushState(std::unique_ptr<State::Game_State> state)
{
    m_stateStack.push(std::move(state));
}


void Application::popState()
{
    if (!m_stateStack.empty()) m_stateStack.pop();
}


namespace
{
    void checkFps ()
    {
        static float frameTimes = 0;
        static int   frames = 0;

        static sf::Clock fpsTimer;
        static sf::Clock printFpsTimer;

        frameTimes += (1000000.0f / fpsTimer.restart().asMicroseconds());
        frames++;

        if (printFpsTimer.getElapsedTime().asSeconds() > 1.0f)
        {
            Debug_Display::addFPS(frameTimes / frames);
            printFpsTimer.restart();
        }
    }
}
