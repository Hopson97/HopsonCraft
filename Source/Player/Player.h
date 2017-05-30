#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <array>

#include "../Physics/AABB.h"
#include "../Entity.h"

#include "../Input/Function_Toggle_Key.h"

namespace Chunk
{
    class Map;
}

class World;
class Camera;

class Player : public Entity
{
    public:
        Player(Camera& camera);

        void input          ();
        void update         (float dt);

        void addForce       (const Vector3& force);

        void doCollisionTest(World& world, float dt);

        AABB box;

    private:
        void collisionTest  (World& world,
                             const Vector3& velocity,
                             float dt);

        void keyBoardInput  ();
        void mouseInput     ();


        Camera* m_p_camera;
        Vector3 m_velocity;

        Toggle_Bool m_flyModeToggle;
        Toggle      m_mouseLock;

        bool m_isOnGround = false;
        bool m_isInLiquid = false;
        bool m_isFlying   = false;
};

#endif // PLAYER_H_INCLUDED
