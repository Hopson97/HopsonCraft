#ifndef PLAYING_H_INCLUDED
#define PLAYING_H_INCLUDED

#include "Game_State.h"
#include "../World/World.h"
#include "../HUD/HUD.h"
#include "../Player/Player.h"
#include "../Temp/Quad.h"

#include "../GUI/GUI.h"

class Application;
class Camera;

struct Frame_Time_Checker
{
    public:
        void         update();
        const float& getFrameTime();
        const float& getFPS();

    private:
        sf::Clock   m_timer;
        sf::Clock   m_updateTimer;
        float       m_frameCount = 0;
        float       m_frameTime  = 0;
        float       m_fps        = 0;
};

namespace State
{
    class Playing : public Game_State
    {
        public:
            Playing(Application& application);

            void input  (sf::Event& e) override;
            void input  (Camera& camera) override;
            void update (Camera& camera, float dt) override;
            void draw   (Renderer::Master& renderer) override;

        private:
            void initHUD();

            World               m_world;
            HUD                 m_hud;
            Player              m_player;
            Frame_Time_Checker  m_frameTimeChecker;
            Quad                m_quady;

            GUI::Panel m_testPanel;
    };
}


#endif // PLAYING_H_INCLUDED
