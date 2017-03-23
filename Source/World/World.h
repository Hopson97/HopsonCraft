#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

#include <unordered_map>
#include <memory>

#include "Block_Editor.h"

#include "Chunk/CSection.h"
#include "Chunk/CMap.h"

class Player;
class Camera;

namespace Renderer
{
    class Master;
}

class World
{
    public:
        float m_facesDrawn    = 0;

        World(const Camera& camera, int32_t worldSize);

        void checkPlayerBounds(Player& player);
        void drawWorld(Renderer::Master& renderer, const Camera& camera);

    private:
        Chunk::Map m_chunks;

        const Camera*   m_p_camera;
        int32_t m_worldSize     = 0;
};

#endif // WORLD_H_INCLUDED
