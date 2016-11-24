#ifndef PLAYER_H
#define PLAYER_H

#include "Camera.h"
#include "../World/Block/Block.h"

namespace sf
{
    class Event;
}

class Player
{
    public:
        Player();

        const Camera& getCamera () const;

        void setPosition(const Vector3& position);

        void input (const sf::Event& e);
        void input ();
        void update (float dt, Camera& camera);

        const Block_t& getBlock() const;

        constexpr static double SPEED = 0.45;

    private:
        void translationInput   ();
        void walkingInput (Vector3& change, float yaw);
        void upDownInput (Vector3& change);

        void rotationInput ();

        void changeBlock (int increment);

        Camera  m_camera;
        Vector3 m_velocity;
        const Block_t* m_p_heldBlock;
};

#endif // PLAYER_H
