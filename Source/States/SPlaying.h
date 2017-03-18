#ifndef PLAYING_H_INCLUDED
#define PLAYING_H_INCLUDED

#include <vector>

#include "Game_State.h"

#include "../Model.h"
#include "../Texture/Texture_Atlas.h"
#include "../World/World.h"
#include "../HUD/HUD.h"
#include "../Player/Player.h"

#include "../Temp/Quad.h"

class Application;
class Camera;

struct Frame_Time_Checker
{
    public:
        void         update();
        const float& getFrameTime();

    private:
        sf::Clock   m_timer;
        sf::Clock   m_updateTimer;
        float       m_frameCount = 0;
        float       m_frameTime  = 0;
};

namespace State
{
    class Playing : public Game_State
    {
        public:
            Playing(Application& application);

            void input  (Camera& camera) override;
            void update (Camera& camera, float dt) override;
            void draw   (Renderer::Master& renderer) override;

        private:
            World               m_world;
            HUD                 m_hud;
            Player              m_player;
            Frame_Time_Checker  m_frameTimeChecker;
            Quad                m_quady;
    };
}


#endif // PLAYING_H_INCLUDED
