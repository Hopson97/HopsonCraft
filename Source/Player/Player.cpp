#include "Player.h"

#include <SFML/Graphics.hpp>

#include <iostream>

#include "../Camera.h"
#include "../World/Block/Block_Database.h"
#include "../World/World.h"
#include "../Maths/General_Maths.h"

Player::Player(Camera& camera)
:   m_p_camera  (&camera)
,   box         ({0.5, 1.7, 0.5})
{ }

void Player::addForce(const Vector3& force)
{
    m_velocity += force;
}

void Player::update(float dt)
{
    //position    += m_velocity * dt;
    box.update(position);
    m_velocity.x  *= 0.95;
    m_velocity.z  *= 0.95; ///@TODO Dampen the velocity using dt

    if (m_isFlying)
    {
        m_velocity.y *= 0.95;
    }
}

void Player::doCollisionTest(World& world, float dt)
{
    if (!m_isFlying)
    {
        if (!m_isOnGround)
        {
            m_velocity.y -= 50 * dt;
        }
        m_isOnGround = false;
        m_isInLiquid = false;
    }

    position.x += m_velocity.x * dt;
    collisionTest(world, dt, m_velocity.x, 0, 0);

    position.y += m_velocity.y * dt;
    collisionTest(world, dt, 0, m_velocity.y, 0);

    position.z += m_velocity.z * dt;
    collisionTest(world, dt, 0, 0, m_velocity.z);
}

void Player::collisionTest(World& world, float dt, float vx, float vy, float vz)
{
    float size      = 0.5;
    float height    = 1.5;

    for (int32_t x = position.x - size    ; x < position.x + size   ; x++)
    for (int32_t y = position.y - height  ; y < position.y + 0.7    ; y++)///@TODO Allow player
    for (int32_t z = position.z - size    ; z < position.z + size   ; z++)///to enter 2 height hole
    {
        auto block = world.getBlock({x, y, z});

        if (block.getData().isObstacle)
        {
            if (vx > 0)
            {
                position.x = x - size;
            }
            if (vx < 0)
            {
                position.x = x + size + 1;
            }
            if (vy > 0)
            {
                position.y = y - height;
                m_velocity.y = 0;
            }
            if (vy < 0)
            {
                position.y = y + height + 1;
                m_isOnGround = true;
                m_velocity.y = 0;
            }
            if (vz > 0)
            {
                position.z = z - size;
            }
            if (vz < 0)
            {
                position.z = z + size + 1;
            }
        }
    }
}

