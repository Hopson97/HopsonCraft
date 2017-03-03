#ifndef PLAYING_H_INCLUDED
#define PLAYING_H_INCLUDED

#include "Game_State.h"

#include "../Model.h"
#include "../Texture/Texture_Atlas.h"

#include "../Temp/Quad.h"

#include "../World/World.h"

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
            World world;

            Quad m_quad;

    };
}


#endif // PLAYING_H_INCLUDED
