#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

#include "Block_Editor.h"

class Player;
class Camera;
class HUD;
class World_File;

namespace Renderer
{
    class Master;
}

class World
{
    public:
        World(const Camera& camera, HUD& hud, World_File& file);

        void input  (Camera& camera);
        void update (float dt);
        void draw   (Renderer::Master& renderer);

    private:
        //Block_Editor m_blockEditor;

        HUD*            m_p_hud;
        const Camera*   m_p_camera;
};

#endif // WORLD_H_INCLUDED
