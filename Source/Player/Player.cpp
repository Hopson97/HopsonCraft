#include "Player.h"

#include <SFML/Graphics.hpp>

#include "../Camera.h"
#include "../World/Chunk/CMap.h"
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
        50,
        150,
        50
    };
}


void Player::testForCollide(Chunk::Map& chunkMap, float dt)
{
    /*
    if (!m_isFlying)
    {
        if (!m_isOnGround && !m_isInLiquid)
        {
            m_velocity.y -= 40 * dt;
        }
        else if (m_isInLiquid)
        {
            m_velocity.y -= 5 * dt;
        }
        m_isOnGround = false;
        m_isInLiquid = false;
    }

    const Block::Data_Holder& b
    = Block::Database::get()
        .getBlock(chunkMap
        .getBlockAt({position.x, position.y - 1, position.z}).id)
        .getData()
        .get();

    if (b.blockID == Block::ID::Water)
    {
        m_isInLiquid = true;
    }
*/
    position.x += m_velocity.x * dt;
    //collisionTest(chunkMap, dt, m_velocity.x, 0, 0);

    position.y += m_velocity.y * dt;
    //collisionTest(chunkMap, dt, 0, m_velocity.y, 0);

    position.z += m_velocity.z * dt;
    //collisionTest(chunkMap, dt, 0, 0, m_velocity.z);

    //box.update(position + (m_velocity * dt));
}

/*
namespace
{
    float size = 0.45;
    float height = 1.75;
}

void Player::collisionTest( Chunk::Map& chunkMap,
                            float dt,
                            float vx,
                            float vy,
                            float vz)
{
    for (int32_t x = position.x - size    ; x < position.x + size     ; x++)
    for (int32_t y = position.y - height  ; y < position.y + height   ; y++)
    for (int32_t z = position.z - size    ; z < position.z + size     ; z++)
    {
        if (Block::Database::get()
            .getBlock(chunkMap
            .getBlockAt({x, y, z}).id)
            .getData()
            .get()
            .isObstacle)
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
*/

void Player::update(float dt)
{
    position += m_velocity * dt;

    if (position.x < 0.2)
    {
        position.x = 0.2;
    }
    if (position.z < 0.2)
    {
        position.z = 0.2;
    }

    m_velocity.x = 0;
    m_velocity.z = 0;

    if(m_isFlying)
        m_velocity.y = 0;
}
