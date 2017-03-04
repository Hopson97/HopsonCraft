#include "Camera.h"

#include <cmath>

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#include "Display.h"

void Camera::input(float dt)
{
    Vector3 change;
    float speed = 25;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        change.x -= cos(glm::radians(rotation.y + 90)) * speed;
        change.z -= sin(glm::radians(rotation.y + 90)) * speed;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        change.x += cos(glm::radians(rotation.y + 90)) * speed;
        change.z += sin(glm::radians(rotation.y + 90)) * speed;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        change.x += -cos(glm::radians(rotation.y)) * speed;
        change.z += -sin(glm::radians(rotation.y)) * speed;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        change.x += cos(glm::radians(rotation.y)) * speed;
        change.z += sin(glm::radians(rotation.y)) * speed;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        change.y += speed;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
    {
        change.y -= speed;
    }

    position += change * dt;

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

    auto centerX = Display::WIDTH   / 2;
    auto centerY = Display::HEIGHT  / 2;

    sf::Mouse::setPosition(sf::Vector2i{centerX, centerY}, Display::get());

    lastMousePosition = sf::Mouse::getPosition();
}













































