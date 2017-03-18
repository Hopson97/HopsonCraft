#include "Application.h"

#include <iostream>
#include <chrono>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>
#include "Resource_Managers/Resource_Holder.h"

#include "windows.h"

#include "Display.h"

#include "States/SPlaying.h"

namespace
{
    sf::Text text;

    void checkFps ()
    {
        static sf::Clock timer;
        static sf::Clock printTimer;
        static float numFrames = 0;

        numFrames++;

        if (printTimer.getElapsedTime().asSeconds() >= 0.5)
        {
            auto FPS = numFrames / timer.getElapsedTime().asMilliseconds();
            if (FPS <= 0) return;

            text.setString("Frame time: " + std::to_string(1/ FPS) + "ms");
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
    sf::Clock gameTimer;
/*
    auto getCurrentTime = [&]()
    {
        return gameTimer.getElapsedTime();
    };
    sf::Time previous = getCurrentTime();
    sf::Time lag;
*/
    while (Display::isOpen())
    {
/*
        sf::Time current    = getCurrentTime();
        sf::Time elapsed    = current  - previous;
        previous            = current ;
        lag                 += elapsed;
*/
        auto elapsed = gameTimer.restart().asSeconds();

        m_musicPlayer.update();

        m_states.back()->input (m_camera);
        //while (lag >= sf::milliseconds(16))
        {
            m_states.back()->update  (m_camera, elapsed);
            m_camera.update();
            //lag -= sf::milliseconds(16);
        }
        m_states.back()->draw    (m_renderer);

        m_renderer.draw(text);
        m_renderer.clear();
        m_renderer.update(m_camera);

        Display::checkForClose();
        checkFps ();
    }
}

void Application::pushState(std::unique_ptr<State::Game_State> state)
{
    m_states.push_back(std::move(state));
}

void Application::popState()
{
    m_states.pop_back();
}

Camera& Application::getCamera()
{
    return m_camera;
}

/*
void Application::runMainGameLoop()
{
    sf::Clock gameTimer;

    std::vector<double> frameTimes;
    double sum = 0;

    auto getCurrentTime = [&]() { return gameTimer.getElapsedTime(); };

    sf::Time lastTime = getCurrentTime();
    while (Display::isOpen())
    {
        sf::Time now = getCurrentTime();
        sf::Time elapsed = now - lastTime;
        lastTime = now;
        lag += elapsed.asMilliseconds();

        m_musicPlayer.update();



        m_states.top()->input   (m_camera);
        m_states.top()->update  (m_camera, elapsed.asSeconds());
        m_camera.update();


        m_states.top()->draw    (m_renderer);
        m_renderer.draw(text);

        m_renderer.clear();
        m_renderer.update(m_camera);

        Display::checkForClose();

        checkFps ();
        frameTimes.push_back(elapsed.asMilliseconds());
        sum += frameTimes.back();

    }


    //render.join();

    frameTimes.erase(frameTimes.begin(), frameTimes.begin() + 750);

    double average = sum / frameTimes.size();

    double sxx = 0;
    for (double f : frameTimes)
    {
        sxx += (f * f);
    }
    sxx -= (frameTimes.size() * (average * average));

    double sd = sqrt(sxx / (frameTimes.size() - 1));

    std::cout   << "Standard deviation: " << sd << " milliseconds\n"
                << "Total Frames:       " << frameTimes.size() << std::endl;

    int outliers = 0;
    for (double f : frameTimes)
    {
        if (f > average + (2 * sd))
            //f < average - (2 * sd)
        {
            outliers++;
        }
    }

    std::sort(frameTimes.begin(), frameTimes.end());
    std::reverse(frameTimes.begin(), frameTimes.end());
    std::cout << "Worst frames: " << std::endl;
    for (int i = 0; i < 25; i++)
    {
        std::cout << frameTimes.at(i) << std::endl;
    }

    std::cout << "Outliers: " << outliers << std::endl;
    std::cout << "Percent:  " << ((float)outliers / (float)frameTimes.size()) * 100.0f << std::endl;
    std::cout << "Average Frame Time " << average << "ms\n";
}
*/
