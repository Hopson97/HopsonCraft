#include "Player.h"

#include <SFML/Graphics.hpp>

#include "../Camera.h"
#include "../World/Block/Block_Database.h"

#include "../Maths/General_Maths.h"

Player::Player(Camera& camera)
:   m_p_camera  (&camera)
,   box         ({0.5, 0.5, 0.5})
{
    resetPosition();
}

void Player::addForce(const Vector3& force)
{
    m_velocity += force;
}

void Player::resetPosition()
{
    position =
    {
        0,
        1.5,
        0
    };

    rotation =
    {
        45,
        45,
        0
    };
}

void Player::update(float dt)
{
    position    += m_velocity * dt;
    m_velocity  *= 0.95;

    if (position.x < 0.2)
    {
        position.x = 0.2;
    }
    if (position.z < 0.2)
    {
        position.z = 0.2;
    }

    if(m_isFlying)
        m_velocity.y *= 0.98;
}
