#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

#include <vector>
#include <memory>

#include <SFML/System/Clock.hpp>


#include "../Physics/AABB.h"

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
        World(const World_Settings& settings);

        void updateChunks();

        void checkPlayerBounds(Player& player);
        void drawWorld(Renderer::Master& renderer, const Camera& camera);

        void qSetBlock  (const Vector3& position, CBlock block);
        void setBlock   (const Vector3& position, CBlock block);
        CBlock getBlock (const Vector3& position);

        uint32_t getHeightAt (const Vector3& worldPosition);

        const World_Settings& getWorldSettings() const;

        void f();

        AABB getBlockAABB(const Block::Position& position);

    private:
        void regenerateChunks   ();
        void buildMeshes        (const Camera& camera);
        void draw               (Renderer::Master& renderer, const Camera& camera);

        std::vector<New_Block> m_newBlocks;

        World_Settings  m_worldSettings;
        Chunk::Map      m_chunks;

        int m_loadingDistance = 1;

    public:
        ///@TODO Make this private somehow.
        ///I say "somehow", as it has to be accessed by the HUD debug display
        float m_facesDrawn = 0;
};

#endif // WORLD_H_INCLUDED
