#include "Camera.h"

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>

#include "Util/Display.h"
#include "Input/Function_Toggle_Key.h"

namespace
{
    bool locked = false;
    static Function_Toggle_Key lock([&]()
    {
        locked = !locked;
        std::cout << "PL" << std::endl;
    },
    sf::Keyboard::L,
    sf::seconds(1.5));
}

void Camera::mouseInput()
{
    lock.checkInput();
    if (locked)
        return;

    static sf::Vector2i lastMousePos;
    auto mouseMove = lastMousePos - sf::Mouse::getPosition();

    rotation.y -= (float)mouseMove.x / 1.5f;// / 0.9;
    rotation.x -= (float)mouseMove.y / 1.5f;// / 0.9;

    if (rotation.x > 80 )
        rotation.x = 80;
    else if (rotation.x < -80)
        rotation.x = -80;

    if (rotation.y < 0 )
        rotation.y = 360;
    else if (rotation.y > 360)
        rotation.y = 0;

    auto windowSize = Display::get().getSize();
    sf::Mouse::setPosition(sf::Vector2i(windowSize.x / 2, windowSize.y / 2), Display::get());

    lastMousePos = sf::Mouse::getPosition();
}

void Camera::movePosition(const Vector3& amount)
{
    position += amount;
}
