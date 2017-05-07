#include "Player.h"

#include <SFML/Graphics.hpp>

#include "../Camera.h"
#include "../World/Block/Block_Database.h"

#include "../Maths/General_Maths.h"

Player::Player(Camera& camera)
:   m_p_camera  (&camera)
,   box         ({0.5, 0.5, 0.5})
{ }

void Player::addForce(const Vector3& force)
{
    m_velocity += force;
}

void Player::update(float dt)
{
    position    += m_velocity * dt;
    m_velocity  = {0, 0, 0}; ///@TODO Dampen the velocity using dt
}
