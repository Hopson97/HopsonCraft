#ifndef PLAYING_H_INCLUDED
#define PLAYING_H_INCLUDED

#include <vector>

#include "Game_State.h"

#include "../Model.h"
#include "../Texture/Texture_Atlas.h"
#include "../World/World.h"
#include "../HUD/HUD.h"
#include "../Player/Player.h"
#include "../File/World_File.h"

#include "../Temp/Quad.h"

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
            World_File  m_worldFile;

            World       m_world;
            HUD         m_hud;

            Player      m_player;

            std::vector<Quad> m_quads;
            Quad m_quady;
    };
}


#endif // PLAYING_H_INCLUDED
