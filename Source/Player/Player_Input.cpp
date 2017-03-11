#include "Player.h"

#include "../Input/Key_Binds.h"
#include "../Input/Function_Toggle_Key.h"
#include "../Display.h"

#include <iostream>

void Player::input()
{
    keyBoardInput();
    mouseInput();

    //rotation = m_p_camera->rotation;
    //m_p_camera->position = position;
}


void Player::keyBoardInput ()
{
    Vector3 change;
    float speed = 0.3;

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
        if (m_isOnGround)
        {
            m_velocity.y += 12;
        }
    }

    addForce(change);
}


void Player::mouseInput ()
{
    static bool lock = false;
    static Function_Toggle_Key key([&](){ lock = !lock; }, sf::Keyboard::L, sf::seconds(1.0));
    key.checkInput();
    if(lock) return;


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

    auto centerX = Display::get().getSize().x / 4;
    auto centerY = Display::get().getSize().y / 4;

    sf::Mouse::setPosition({centerX, centerY}, Display::get());

    lastMousePosition = sf::Mouse::getPosition();
}
