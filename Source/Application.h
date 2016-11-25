#ifndef APPLICATION_H
#define APPLICATION_H

#include <stack>
#include <memory>

#include <SFML/Audio.hpp>

#include "Game_States/Game_State.h"
#include "Renderer/Master_Renderer.h"
#include "Player/Camera.h"

class Application
{
    public:
        Application ();
        ~Application();

        void runMainLoop();

        void changeState    (std::unique_ptr<State::Game_State> state);
        void pushState      (std::unique_ptr<State::Game_State> state);
        void popState       ();

        void takeScreenshot (const std::string& path = "-1");
        void resetSong();

    private:
        void init();

        std::stack<std::unique_ptr<State::Game_State>> m_stateStack;

        sf::Music m_song;
        sf::Time  m_songDuration;
        sf::Clock m_songTimer;

        Master_Renderer m_renderer;
        Camera          m_camera;
};

#endif // APPLICATION_H
