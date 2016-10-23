#include "Camera.h"
#include "Display.h"

void Camera :: update ()
{
    sf::Vector2i mouseMove = m_lastMosuePos - sf::Mouse::getPosition(Display::get());

    m_rotation.y -= mouseMove.x;    //Remember the Y-Axis is Up and Down so rotating around it would be Left-Right
    m_rotation.x -= mouseMove.y;    //Hence the kind of inversion here

    m_lastMosuePos = sf::Mouse::getPosition(Display::get());

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
