#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

#include "Chunk/Chunklet.h"

class Camera;

namespace Renderer
{
    class Master;
}

class World
{
    public:
        World();

        void input  (Camera& camera);
        void update (float dt);
        void draw   (Renderer::Master& renderer);

    private:
        Chunklet m_chunklet;
};

#endif // WORLD_H_INCLUDED
