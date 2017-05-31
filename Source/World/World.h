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

    public:
        World(const World_Settings& settings, const Camera& camera);

        const World_Settings& getWorldSettings () const;

        AABB getBlockAABB(const Block::Position& position);

        void setBlock   (int x, int y, int z, CBlock block) override;
        CBlock getBlock (int x, int y, int z) const override;

    private:
        World_Settings  m_worldSettings;
        const Camera* m_pCamera = nullptr;

    public:
        ///@TODO Make this private somehow.
        ///I say "somehow", as it has to be accessed by the HUD debug display
        float m_facesDrawn = 0;
};

#endif // WORLD_H_INCLUDED
