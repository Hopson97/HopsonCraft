#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

#include <vector>
#include <memory>

#include "Block_Editor.h"

#include "Chunk/CSection.h"
#include "Chunk/CMap.h"

#include "World_Settings.h"

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
        New_Block(CBlock newBlock, const Vector3& blockPosition)
        :   block       (newBlock)
        ,   position    (blockPosition)
        { }

        CBlock block;
        Vector3 position;
    };

    public:
        World(const Camera& camera, const World_Settings& settings);

        void checkPlayerBounds(Player& player);
        void drawWorld(Renderer::Master& renderer, const Camera& camera);

        void setBlock   (const Vector3& position, CBlock block);
        CBlock getBlock (const Vector3& position);

        uint32_t getHeightAt (const Vector3& worldPosition);

        const World_Settings& getWorldSettings() const;

    private:
        void regenerateChunks();
        void buffer(const Camera& camera);
        void draw  (Renderer::Master& renderer, const Camera& camera);

        std::vector<New_Block> m_newBlocks;

        Chunk::Map      m_chunks;
        World_Settings  m_worldSettings;
        int32_t         m_loadingDistance = 1;
        const Camera*   m_p_camera;

    public:
        float m_facesDrawn = 0;
};

#endif // WORLD_H_INCLUDED
