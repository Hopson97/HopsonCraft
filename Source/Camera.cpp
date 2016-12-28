#include "Camera.h"

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>

#include "Util/Display.h"
#include "Input/Function_Toggle_Key.h"
#include "Input/Key_Binds.h"
#include "Maths/General_Maths.h"

namespace
{
    bool locked = false;
    static Function_Toggle_Key lock([&]()
    {
        locked = !locked;
    },
    sf::Keyboard::L,
    sf::seconds(1.5));
}

Vector3 Camera::keyboardInput(float speed)
{
    if (locked)
        return {0, 0, 0};
    //Speed variables

    Vector3 change;
    auto acc = sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) ?
        speed * 10.0 :
        speed;

    auto yaw = glm::radians(rotation.y);

    if  (sf::Keyboard::isKeyPressed(Key_Binds::getKey(Key_Binds::Control::Player_Forwards)))
    {
        change.x -= cos (yaw + Maths::PI / 2) * acc;
        change.z -= sin (yaw + Maths::PI / 2) * acc;
    }
    if  (sf::Keyboard::isKeyPressed(Key_Binds::getKey(Key_Binds::Control::Player_Back)))
    {
        change.x += cos (yaw + Maths::PI / 2) * acc;
        change.z += sin (yaw + Maths::PI / 2) * acc;
    }
    if  (sf::Keyboard::isKeyPressed(Key_Binds::getKey(Key_Binds::Control::Player_Right)))
    {
        change.x += cos (yaw) * acc;
        change.z += sin (yaw) * acc;
    }
    if  (sf::Keyboard::isKeyPressed(Key_Binds::getKey(Key_Binds::Control::Player_Left)))
    {
        change.x -= cos (yaw) * acc;
        change.z -= sin (yaw) * acc;
    }


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
    {
        change.y -= acc;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        change.y += acc;
    }

    return change;
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
