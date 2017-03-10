#include "Player.h"

#include <SFML/Graphics.hpp>

#include "Camera.h"
#include "World/Chunk/CMap.h"



Player::Player(Camera& camera)
:   m_p_camera  (&camera)
,   box         ({0.5, 0.5, 0.5})
{
    position = {50,100, 50};
}

void Player::addForce(const Vector3& force)
{
    m_velocity += force;
}

void Player::testForCollide(Chunk::Map& chunkMap, float dt)
{
    box.update(position + (m_velocity * dt));
}



void Player::input()
{
    /*
    static sf::Clock c;
    if (c.getElapsedTime().asSeconds() >= 0.5)
    {
        std::cout << "Y: " << position.y << std::endl;
        c.restart();
    }
    */
    addForce(m_p_camera->input());
    rotation = m_p_camera->rotation;
    m_p_camera->position = position;
}

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

    m_velocity *= 0.95;
}
