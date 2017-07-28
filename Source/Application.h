#ifndef APPLICATION_H_INCLUDED
#define APPLICATION_H_INCLUDED

#include <vector>
#include <memory>

#include "States/StateBase.h"

#include "Renderer/MasterRenderer.h"

#include "Camera.h"
#include "MusicPlayer.h"

class Application
{
    public:
        Application();

        void runMainGameLoop();



        Camera& getCamera();

        void resetSong();

        MusicPlayer musicPlayer;

        template<typename S, typename... Args>
        void pushState(Args&&... args)
        {
            m_states.push_back(std::make_unique<S>(std::forward<Args>(args)...));
            currentState().onOpen();
        }

        void popState();

    private:
        void handleEvents();

        StateBase& currentState();

        std::vector<std::unique_ptr<StateBase>> m_states;
        MasterRenderer m_renderer;
        Camera m_camera;

        bool m_shouldPop = false;
};

#endif // APPLICATION_H_INCLUDED
