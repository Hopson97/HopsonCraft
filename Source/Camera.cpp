#include "Camera.h"

#include <SFML/Graphics.hpp>

void Camera :: move ( float dt )
{
    float speed;
    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::LControl) )
    {
        speed = 50 * dt;
    }
    else speed = 10 * dt;

    if  ( sf::Keyboard::isKeyPressed( sf::Keyboard::W ) )
    {
        m_position.z -= speed;
    }
    if  ( sf::Keyboard::isKeyPressed( sf::Keyboard::D ) )
    {
        m_position.x += speed;
    }
    if  ( sf::Keyboard::isKeyPressed( sf::Keyboard::A ) )
    {
        m_position.x -= speed;
    }
    if  ( sf::Keyboard::isKeyPressed( sf::Keyboard::S ) )
    {
        m_position.z += speed;
    }

    if  ( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) )
    {
        m_rotation.y -= speed * 5;
    }
    if  ( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) )
    {
        m_rotation.y += speed * 5;
    }

    if  ( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) )
    {
        m_rotation.x -= speed * 5;
    }
    if  ( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) )
    {
        m_rotation.x += speed * 5;
    }

    if  ( sf::Keyboard::isKeyPressed( sf::Keyboard::Space ) )
    {
        m_position.y += speed;
    }
    if  ( sf::Keyboard::isKeyPressed( sf::Keyboard::LShift ) )
    {
        m_position.y -= speed;
    }
}

const Vector3& Camera :: getPosition() const
{
    return m_position;
}

const Vector3& Camera :: getRotation() const
{
    return m_rotation;
}

void Camera::movePosition(const Vector3& position)
{
    m_position = position;
}

