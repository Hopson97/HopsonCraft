#include "Application.h"

#include "Display.h"
#include "OpenGL/GLEW/glew.h"

#include <cstdlib>
#include <iostream>
#include <string>

#include "Debug_Display.h"
#include "Game_States/Playing_State.h"
#include "Random.h"
#include <ctime>

namespace
{
    void checkFps ();
}

Application::Application()
{
    srand(time(nullptr));
    std::cout << "Starting app!" << std::endl;
    m_stateStack.push(std::make_unique<State::Playing_State>(*this));
    resetSong();
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

        if(m_songTimer.getElapsedTime() > m_songDuration )
        {
            resetSong();
        }
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

void Application::resetSong()
{
    static std::string songFilesPath = "Data/Music/";
    static std::vector<std::string> songNames =
    {
        "C418-Ward",
        "C418-Sweden(Caution and Crisis Remix)"
    };
    static auto lastSong = songNames.size() - 1; //In terms of the index in the std::vector
    auto thisSong = lastSong;

    while (thisSong != lastSong) thisSong = Random::integer(0, songNames.size() - 1);

    lastSong = thisSong;
    m_song.openFromFile(songFilesPath + songNames.at(thisSong) + ".ogg");
    m_song.play();
    m_songDuration = m_song.getDuration();
    m_songTimer.restart();

    std::cout << "Switched song" << std::endl;
}


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
            Debug_Display::addFPS(fps);

            numFrames = 0;
            timer.restart();
        }
/*
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
        */
    }

}
