#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <array>

#include "Physics/AABB.h"
#include "Body.h"

namespace Chunk
{
    class Map;
}

class Camera;

class Player : public Entity
{
    public:
        Player(Camera& camera);

        void input          ();
        void testForCollide (Chunk::Map& chunkMap, float dt);
        void update         (float dt);

        void addForce       (const Vector3& force);

    private:
        Camera* m_p_camera;
        Vector3 m_velocity;

    public:
        AABB box;
};

#endif // PLAYER_H_INCLUDED
