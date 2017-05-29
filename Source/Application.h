#ifndef APPLICATION_H_INCLUDED
#define APPLICATION_H_INCLUDED

#include <vector>
#include <memory>

#include "States/Game_State.h"

#include "Renderer/RMaster.h"

#include "Camera.h"
#include "Music_Player.h"

class Application
{
    public:
        Application();

        void runMainGameLoop();

        void pushState(std::unique_ptr<State::Game_State> state);
        void popState();

        Camera& getCamera();

        void resetSong();

        Music_Player musicPlayer;

    private:
        void handleEvents();
        void update(float elapsed);
        void render();



        std::vector<std::unique_ptr<State::Game_State>> m_states;
        Renderer::Master m_renderer;
        Camera m_camera;
};

#endif // APPLICATION_H_INCLUDED
