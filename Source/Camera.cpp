#include "Camera.h"

#include <cmath>

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#include "Display.h"
#include "Input/Key_Binds.h"

void Camera::input()
{
    Vector3 change;
    float speed = 0.01;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
    {
        speed = 0.2;
    }

    if (sf::Keyboard::isKeyPressed(Key_Binds::getKey(Key_Binds::Control::Player_Forwards)))
    {
        change.x -= cos(glm::radians(rotation.y + 90)) * speed;
        change.z -= sin(glm::radians(rotation.y + 90)) * speed;
    }

    if (sf::Keyboard::isKeyPressed(Key_Binds::getKey(Key_Binds::Control::Player_Back)))
    {
        change.x += cos(glm::radians(rotation.y + 90)) * speed;
        change.z += sin(glm::radians(rotation.y + 90)) * speed;
    }

    if (sf::Keyboard::isKeyPressed(Key_Binds::getKey(Key_Binds::Control::Player_Left)))
    {
        change.x += -cos(glm::radians(rotation.y)) * speed;
        change.z += -sin(glm::radians(rotation.y)) * speed;
    }

    if (sf::Keyboard::isKeyPressed(Key_Binds::getKey(Key_Binds::Control::Player_Right)))
    {
        change.x += cos(glm::radians(rotation.y)) * speed;
        change.z += sin(glm::radians(rotation.y)) * speed;
    }

    if (sf::Keyboard::isKeyPressed(Key_Binds::getKey(Key_Binds::Control::Player_Up)))
    {
        change.y += speed;
    }

    if (sf::Keyboard::isKeyPressed(Key_Binds::getKey(Key_Binds::Control::Player_Down)))
    {
        change.y -= speed;
    }

    m_velocity += change;

    mouseInput();
}


void Camera::mouseInput()
{
    static sf::Vector2i lastMousePosition = sf::Mouse::getPosition();

    auto mouseChange = sf::Mouse::getPosition() - lastMousePosition;

    rotation.y += mouseChange.x;
    rotation.x += mouseChange.y;

    if (rotation.x > 80)
    {
        rotation.x = 80;
    }
    else if (rotation.x < -80)
    {
        rotation.x = -80;
    }
    if (rotation.y < 0)
    {
        rotation.y = 360;
    }
    else if (rotation.y > 360)
    {
        rotation.y = 0;
    }

    auto centerX = Display::get().getSize().x / 2;
    auto centerY = Display::get().getSize().y / 2;

    sf::Mouse::setPosition({centerX, centerY}, Display::get());

    lastMousePosition = sf::Mouse::getPosition();
}



void Camera::update(float dt)
{
    m_velocity *= 0.95;
}

const Vector3& Camera::getVelocity() const
{
    return m_velocity;
}













































