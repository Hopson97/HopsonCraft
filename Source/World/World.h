#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

#include <unordered_map>
#include <memory>

#include "Block_Editor.h"

#include "Chunk/CSection.h"

class Player;
class Camera;

namespace Renderer
{
    class Master;
}

class World
{
    public:
        World(const Camera& camera, uint32_t worldSize);

        void checkPlayerBounds(Player& player);
        void drawWorld(Renderer::Master& renderer);

    private:
        std::unordered_map<Chunk::Position, std::unique_ptr<Chunk::Section>> m_chunkSection;

        const Camera*   m_p_camera;
        uint32_t m_worldSize = 0;

};

#endif // WORLD_H_INCLUDED
