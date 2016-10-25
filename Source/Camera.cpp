#include "Camera.h"

#include <iostream>

#include "Display.h"

void Camera :: update ()
{
    sf::Vector2i mouseMove = m_lastMosuePos - sf::Mouse::getPosition( Display::get() );

    m_rotation.y -= mouseMove.x;
    m_rotation.x -= mouseMove.y;

    m_lastMosuePos = sf::Mouse::getPosition( Display::get() );
/*
    sf::Mouse::setPosition( { Display::WIDTH / 2, Display::HEIGHT / 2 },
                              Display::get() );
*/
    if ( m_rotation.x > 80 ) m_rotation.x = 80;
    else if ( m_rotation.x < -80 ) m_rotation.x = -80;
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
    m_position += position;
}
