#ifndef PLAYING_H_INCLUDED
#define PLAYING_H_INCLUDED

#include "Base.h"
#include "../World/World.h"
#include "../HUD/HUD.h"
#include "../Player/Player.h"
#include "../Entity/Cube.h"

#include "../Util/TimeCheck.h"

#include "../GUI/Panel.h"

class Application;
class Camera;
class WorldSettings;

namespace State
{
    class Playing : public Base
    {
        public:
            Playing(Application& application,
                    const WorldSettings& settings);

            void input      (const sf::Event& e)        override;
            void input      (Camera& camera)            override;
            void update     (Camera& camera, float dt)  override;
            void fixedUpdate(Camera& camera, float dt)  override;
            void draw       (Renderer::Master& renderer)override;

            void onOpen() override;

        private:
            void editBlockInput();

            Vector3 getCenterPosition();

            void initHUD();
            void initPause();

            World               m_world;
            HUD                 m_hud;
            Debug_HUD           m_debugHud;
            Player              m_player;
            FrameTimeChecker  m_tickRate;
            FrameTimeChecker  m_frameRate;
            std::vector<Cube>   m_cubes;

            GUI::Panel m_pauseMenu;

            bool                m_isPaused = false;
    };
}


#endif // PLAYING_H_INCLUDED
