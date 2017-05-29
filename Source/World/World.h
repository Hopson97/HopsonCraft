#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

#include <vector>
#include <memory>
#include <thread>
#include <mutex>

#include <SFML/System/Clock.hpp>

#include "../Physics/AABB.h"

#include "World_Settings.h"

#include "IBlock_Accessible.h"

class Player;
class Camera;

namespace Renderer
{
    class Master;
}

namespace State
{
    class Playing;
}

class World : public IBlock_Accessible
{
    friend class State::Playing;

    enum class State
    {
        Nothing,
        Regenerating,
        Triggering,
    } m_state = State::Nothing;


    struct Position_Block
    {
        Position_Block(CBlock newBlock, const Vector3& blockPosition)
        :   block       (newBlock)
        ,   position    (blockPosition)
        { }

        CBlock block;
        Vector3 position;
    };

    public:
        World(const World_Settings& settings, const Camera& camera);
        ~World();

        void updateChunks(const Player& player);

        void checkPlayerBounds(Player& player);
        void drawWorld(Renderer::Master& renderer, const Camera& camera);

        uint32_t getHeightAt (const Vector3& worldPosition);

        const World_Settings&   getWorldSettings    () const;

        AABB getBlockAABB(const Block::Position& position);

        void setBlock   (int x, int y, int z, CBlock block) override;
        CBlock getBlock (int x, int y, int z) const override;

    private:
        void regenerateChunks   ();
        void triggerBlocks      ();
        void generateWorld      (const Camera& camera);

        void checkChunksForDelete();

        std::vector<Position_Block> m_newBlocks;

        World_Settings  m_worldSettings;

        const Camera* m_pCamera = nullptr;

    public:
        ///@TODO Make this private somehow.
        ///I say "somehow", as it has to be accessed by the HUD debug display
        float m_facesDrawn = 0;
};

#endif // WORLD_H_INCLUDED
