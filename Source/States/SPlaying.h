#ifndef PLAYING_H_INCLUDED
#define PLAYING_H_INCLUDED

#include "Game_State.h"

#include "../Model.h"
#include "../Texture/Texture_Atlas.h"

#include "../World/World.h"

#include "../HUD/Vignette.h"
#include "../HUD/Crosshair.h"

#include "../Player.h"

class Application;
class Camera;

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
            World       m_world;
            Vignette    m_vignette;
            Crosshair   m_crosshair;

            Player      m_player;
    };
}


#endif // PLAYING_H_INCLUDED