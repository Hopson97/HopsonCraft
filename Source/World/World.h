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
    struct New_Block
    {
        New_Block(CBlock block, const Vector3& position)
        :   block       (block)
        ,   position    (position)
        { }

        CBlock block;
        Vector3 position;
    };

    public:
        float m_facesDrawn    = 0;

        World(const Camera& camera, int32_t worldSize);

        void checkPlayerBounds(Player& player);
        void drawWorld(Renderer::Master& renderer, const Camera& camera);

        void setBlock   (const Vector3& position, CBlock block);
        CBlock getBlock (const Vector3& position);

        void addSectionUpdate(Chunk::Section* section);

    private:
        void regenerateChunks();
        void buffer(const Camera& camera);
        void draw  (Renderer::Master& renderer, const Camera& camera);

        std::vector<Chunk::Section*> m_sectionsToUpdate;
        std::vector<New_Block> m_newBlocks;

        Chunk::Map m_chunks;

        const Camera*   m_p_camera;
        int32_t m_worldSize     = 0;
};

#endif // WORLD_H_INCLUDED
