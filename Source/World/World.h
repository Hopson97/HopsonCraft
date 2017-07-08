#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

#include <vector>
#include <memory>
#include <thread>
#include <mutex>

#include <SFML/System/Clock.hpp>

#include "../Physics/AABB.h"

#include "WorldSettings.h"

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

class World
{
    friend class State::Playing;

    public:
        World(const WorldSettings& settings, const Camera& camera);

        const WorldSettings& getWorldSettings () const;

    private:
        WorldSettings  m_worldSettings;
        const Camera* m_pCamera = nullptr;

    public:
        ///@TODO Make this private somehow.
        ///I say "somehow", as it has to be accessed by the HUD debug display
        float m_facesDrawn = 0;
};

#endif // WORLD_H_INCLUDED
