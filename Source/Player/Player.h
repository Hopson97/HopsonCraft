#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <array>

#include "../Physics/AABB.h"
#include "../Entity.h"

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
        void update         (float dt);

        void addForce       (const Vector3& force);

    private:
        void resetPosition();

        void keyBoardInput  ();
        void mouseInput     ();


        Camera* m_p_camera;
        Vector3 m_velocity;

        bool m_isOnGround = false;
        bool m_isInLiquid = false;
        bool m_isFlying   = true;

    public:
        AABB box;
};

#endif // PLAYER_H_INCLUDED
