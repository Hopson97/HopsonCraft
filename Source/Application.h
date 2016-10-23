#ifndef APPLICATION_H
#define APPLICATION_H

#include <stack>
#include <memory>

#include "Game_State.h"

class Application
{
    public:
        Application();

        void runMainLoop();

        void pushState  (std::unique_ptr<State::Game_State> state);

    private:
        std::stack<std::unique_ptr<State::Game_State>> m_stateStack;

};

#endif // APPLICATION_H
