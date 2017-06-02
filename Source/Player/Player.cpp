#include "Player.h"

#include <SFML/Graphics.hpp>

#include <iostream>

#include "../Camera.h"
#include "../World/Block/Block_Database.h"
#include "../World/World.h"
#include "../Maths/General_Maths.h"

Player::Player(Camera& camera)
:   box             ({0.5, 1.5, 0.5})
,   m_p_camera      (&camera)
,   m_flyModeToggle {sf::Keyboard::F, sf::seconds(0.3), m_isFlying}
,   m_mouseLock     {sf::Keyboard::L, sf::seconds(0.5)}
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
    float gravity = 50.0f;

    if (!m_isFlying)
    {
        if (!m_isOnGround && !m_isInLiquid)
        {
            m_velocity.y -= gravity * dt;
        }
        else if (m_isInLiquid)
        {
            m_velocity.y -= (gravity / 10) * dt;
        }
        m_isOnGround = false;
    }

    position.x += m_velocity.x * dt;
    collisionTest(world, {m_velocity.x, 0, 0}, dt);

    position.y += m_velocity.y * dt;
    collisionTest(world, {0, m_velocity.y, 0}, dt);

    position.z += m_velocity.z * dt;
    collisionTest(world, {0, 0, m_velocity.z}, dt);
}

void Player::collisionTest(World& world,
                           const Vector3& velocity,
                           float dt)
{
    const auto& dim = box.getDimensions();

    ///@TODO Allow player
    ///to enter 2 height hole
    for (int32_t x = position.x - dim.x ; x < position.x + dim.x    ; x++)
    for (int32_t y = position.y - dim.y ; y < position.y + 0.7      ; y++)
    for (int32_t z = position.z - dim.z ; z < position.z + dim.z    ; z++)
    {
        auto block = world.getBlock({x, y, z});

        m_isInLiquid = (block.getData().state == Block::State::Liquid);

        if (block.getData().isObstacle)
        {
            if (velocity.x > 0)
            {
                position.x = x - dim.x;
            }
            if (velocity.x < 0)
            {
                position.x = x + dim.x + 1;
            }
            if (velocity.y > 0)
            {
                position.y = y - dim.y;
                m_velocity.y = 0;
            }
            if (velocity.y < 0)
            {
                position.y = y + dim.y + 1;
                m_isOnGround = true;
                m_velocity.y = 0;
            }
            if (velocity.z > 0)
            {
                position.z = z - dim.z;
            }
            if (velocity.z < 0)
            {
                position.z = z + dim.z + 1;
            }
        }
    }
}

