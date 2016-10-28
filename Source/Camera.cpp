#include "Camera.h"

#include <iostream>

#include "Display.h"
#include "Debug_Display.h"

#include "Maths/Matrix_Maths.h"

void Camera::update ()
{
    auto mouseMove = m_lastMosuePos - sf::Mouse::getPosition(Display::get());

    m_rotation.y -= (float)mouseMove.x / 0.9;
    m_rotation.x -= (float)mouseMove.y / 0.9;

    m_lastMosuePos = sf::Mouse::getPosition(Display::get());

    if      (m_rotation.x > 80 ) m_rotation.x = 80;
    else if (m_rotation.x < -80) m_rotation.x = -80;

    if      (m_rotation.y < 0 ) m_rotation.y = 360;
    else if (m_rotation.y > 360) m_rotation.y = 0;

    Debug_Display::addLookVector(m_rotation);
}

const Vector3& Camera::getPosition() const
{
    return m_position;
}

const Vector3& Camera::getRotation() const
{
    return m_rotation;
}

void Camera::movePosition(const Vector3& position)
{
    m_position += position;
}
