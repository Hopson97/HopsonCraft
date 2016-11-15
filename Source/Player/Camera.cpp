#include "Camera.h"

#include <iostream>

#include "../Util/Display.h"
#include "../Util/Debug_Display.h"

#include "../Maths/Matrix_Maths.h"

#include "../Input/Function_Toggle_Key.h"

bool kekpressed = false;


void Camera::update ()
{
    auto mouseMove = m_lastMosuePos - sf::Mouse::getPosition(Display::get());

    m_rotation.y -= (float)mouseMove.x / 0.9;
    m_rotation.x -= (float)mouseMove.y / 0.9;

    m_lastMosuePos = sf::Mouse::getPosition(Display::get());

    static Function_Toggle_Key key([&](){ kekpressed = !kekpressed; }, sf::Keyboard::R, 0.5);

    key.checkInput();

    if(kekpressed)
    {
        m_rotation.y += 0.1;
    }

    if      (m_rotation.x > 80 ) m_rotation.x = 80;
    else if (m_rotation.x < -80) m_rotation.x = -80;

    if      (m_rotation.y < 0 ) m_rotation.y = 360;
    else if (m_rotation.y > 360) m_rotation.y = 0;
}

void Camera::setPosition(const Vector3& position)
{
    m_position = position;
}

void Camera::setRotation(const Vector3& rotation)
{
    m_rotation = rotation;
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
