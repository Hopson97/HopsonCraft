#include "Camera.h"

#include <iostream>

#include "Display.h"
#include "Debug_Display.h"

#include "Maths/Matrix_Maths.h"

void Camera::update ()
{
    static sf::Clock c;
    if (c.getElapsedTime().asSeconds() > 2)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
        {
            std::cout << "TEST" << std::endl;

            Vector4 vector(0, 0, -1, 0);
            auto viewMatrix     = Maths::createViewRotatationMatrix(m_rotation);
            auto worldPosition  = viewMatrix * vector;
            auto scaler = 0.1f;

            Vector4 translation (m_position.x, m_position.y, m_position.z, 0);



            Vector4 end = worldPosition + scaler * translation;

            c.restart();
        }
    }



    auto mouseMove = m_lastMosuePos - sf::Mouse::getPosition(Display::get());

    m_rotation.y -= mouseMove.x;
    m_rotation.x -= mouseMove.y;

    m_lastMosuePos = sf::Mouse::getPosition(Display::get());
/*
    sf::Mouse::setPosition({ Display::WIDTH / 2,
                            Display::HEIGHT / 2 },
                              Display::get() );
*/
    if (m_rotation.x > 80) m_rotation.x = 80;
    else if ( m_rotation.x < -80) m_rotation.x = -80;

    if (m_rotation.y < 0 ) m_rotation.y = 360;
    if (m_rotation.y > 360) m_rotation.y = 0;

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
