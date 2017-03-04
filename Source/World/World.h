#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

#include "Chunk/CMap.h"

class Camera;

namespace Renderer
{
    class Master;
}

class World
{
    public:
        World(const Camera& camera);

        void input  (Camera& camera);
        void update (float dt);
        void draw   (Renderer::Master& renderer);

    private:
        Chunk::Map m_chunkMap;
};

#endif // WORLD_H_INCLUDED
