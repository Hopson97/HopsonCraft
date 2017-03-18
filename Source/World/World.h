#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

#include "Block_Editor.h"

class Player;
class Camera;
class HUD;

namespace Renderer
{
    class Master;
}

class World
{
    public:
        World(const Camera& camera);

    private:
        //Block_Editor m_blockEditor;

        HUD*            m_p_hud;
        const Camera*   m_p_camera;
};

#endif // WORLD_H_INCLUDED
