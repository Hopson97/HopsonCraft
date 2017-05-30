#ifndef PLAYING_H_INCLUDED
#define PLAYING_H_INCLUDED

#include "Game_State.h"
#include "../World/World.h"
#include "../HUD/HUD.h"
#include "../Player/Player.h"
#include "../Temp/Quad.h"

#include "../GUI/GUI.h"
#include "../Util/Time_Check.h"

class Application;
class Camera;
class World_Settings;

namespace State
{
    class Playing : public Game_State
    {
        struct Hit_Info
        {
            bool    isHit = false;
            Vector3 location;
        } m_hitInfo;

        public:
            Playing(Application& application,
                    const World_Settings& settings);

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
            Frame_Time_Checker  m_tickRate;
            Frame_Time_Checker  m_frameRate;
            Quad                m_quady;

            GUI::Panel m_pauseMenu;

            bool                m_isPaused = false;
    };
}


#endif // PLAYING_H_INCLUDED
