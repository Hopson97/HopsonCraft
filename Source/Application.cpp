#include "Application.h"

#include "Util/Display.h"
#include <GL/glew.h>

#include <cstdlib>
#include <string>
#include <ctime>
#include <stdexcept>
#include <chrono>

#include "Game_States/Playing_State.h"
#include "Game_States/Menu_State.h"

#include "Util/Random.h"
#include "Util/Debug_Display.h"
#include "Util/Display.h"
#include "Util/Noise_Generator.h"
#include "Util/Directory_Creator.h"
#include "Util/Time.h"

#include "World/Block/D_Blocks.h"

#include "Play_Settings.h"

namespace
{
    void checkFps ();
}

Application::Application()
{
    init();
    m_stateStack.push(std::make_unique<State::Playing_State>(*this, "Test World", 800819));
}

Application::~Application()
{
    while(!m_stateStack.empty())
    {
        popState();
    }
}

//Main loop!
void Application::runMainLoop()
{
    sf::Clock dtClock;

    while (Display::isOpen())
    {
        auto dt = dtClock.restart().asSeconds();

        sf::Event e;
        while (Display::get().pollEvent(e))
        {
            if (Display::checkForClose(e))
                return;
            m_stateStack.top()->input (e);
        }
        if (!Display::isOpen()) break;

        m_stateStack.top()->input ();

        {
            m_stateStack.top()->update (dt, m_camera);
        }

        m_stateStack.top()->draw (dt, m_renderer);

        m_renderer.clear();
        m_renderer.update(m_camera);

        checkFps();
        if(m_songTimer.getElapsedTime() > m_songDuration )
            resetSong();
    }
}

void Application::changeState(std::unique_ptr<State::Game_State> state)
{
    popState();
    pushState(std::move(state));
}


void Application::pushState(std::unique_ptr<State::Game_State> state)
{
    m_stateStack.push(std::move(state));
}

void Application::popState()
{
    if (!m_stateStack.empty())
    {
        m_stateStack.top()->exitState();
        m_stateStack.pop();
    }
}

void Application::resetSong()
{
    static std::string songFilesPath = "Data/Music/";
    static std::vector<std::string> songNames =
    {
        "C418-Ward",
        "C418-Sweden(Caution and Crisis Remix)",
        "Waterflame - Glorious Morning",
        "The Bird And The Worm Instrumental",
        "Rue's Whistle",
        "Undertale - Once Upon A Time",
        "euk",
    };
    static auto lastSong = songNames.size() - 1; //In terms of the index in the std::vector
    auto thisSong = lastSong;   //Get the Index of the last song

    while (thisSong == lastSong) //So that the new song to play is not the same as the first
        thisSong = Random::integer(0, songNames.size() - 1);

    lastSong = thisSong; //The new song playing is now technically the last song
    m_song.openFromFile(songFilesPath + songNames[thisSong] + ".ogg");
    m_song.play();
    m_songDuration = m_song.getDuration();
    m_songTimer.restart();
    m_song.setVolume(5);
}

void Application::init()
{
    //Generate the base random seed
    Random::setSeed(time(nullptr));

    //Start the music
    resetSong();

    //St up the global/ base seed for the noise functions
    Noise::setSeed(Random::integer(0, 32000) * Random::integer(0, 32000));

    //Initiate the block database
    Block::initBlockDatabase();

    //Initiate the debug information GUI
    Debug_Display::init();

    Settings::load();
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
    }

}
