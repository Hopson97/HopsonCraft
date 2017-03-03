#ifndef APPLICATION_H_INCLUDED
#define APPLICATION_H_INCLUDED

#include <stack>
#include <memory>

#include "States/Game_State.h"

#include "Renderer/RMaster.h"

#include "Entity.h"
#include "Camera.h"

class Application
{
    public:
        Application();

        void runMainGameLoop();

        void pushState(std::unique_ptr<State::Game_State> state);
        void popState();

    private:
        std::stack<std::unique_ptr<State::Game_State>> m_states;

        Renderer::Master m_renderer;

        Camera camera;
};

#endif // APPLICATION_H_INCLUDED
