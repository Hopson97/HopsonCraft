#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

#include "Chunk/CMap.h"

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
        World(const Camera& camera, Player& player, HUD& hud, World_File& file);

        void input  (Camera& camera);
        void update (float dt);
        void draw   (Renderer::Master& renderer);

    private:
        Chunk::Map m_chunkMap;
        Block_Editor m_blockEditor;

        Player*     m_p_player;
        HUD*        m_p_hud;
};

#endif // WORLD_H_INCLUDED
