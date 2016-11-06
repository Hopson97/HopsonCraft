#ifndef APPLICATION_H
#define APPLICATION_H

#include <stack>
#include <memory>

#include <SFML/Audio.hpp>

#include "Game_States/Game_State.h"

class Application
{
    public:
        Application ();
        ~Application();

        void runMainLoop();

        void pushState  (std::unique_ptr<State::Game_State> state);
        void popState   ();

    private:
        void resetSong();

        std::stack<std::unique_ptr<State::Game_State>> m_stateStack;

        sf::Music m_song;
        sf::Time  m_songDuration;
        sf::Clock m_songTimer;
};

#endif // APPLICATION_H
