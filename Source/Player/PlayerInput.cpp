#include "Player.h"

#include "../Input/KeyBinds.h"
#include "../Input/FunctionToggleKey.h"
#include "../Display.h"

void Player::input()
{
    keyBoardInput();
    mouseInput();
}


void Player::keyBoardInput ()
{
    Vector3 change;
    float speed = 0.2;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
    {
        speed *= 3;
    }

    if(m_isInLiquid) speed /= 1.5;

    float yaw   = glm::radians(rotation.y);
    float yaw90 = glm::radians(rotation.y + 90);

    if (sf::Keyboard::isKeyPressed(KeyBinds::getKey(KeyBinds::Control::Player_Forwards)))
    {
        change.x -= glm::cos(yaw90) * speed;
        change.z -= glm::sin(yaw90) * speed;
    }

    if (sf::Keyboard::isKeyPressed(KeyBinds::getKey(KeyBinds::Control::Player_Back)))
    {
        change.x += glm::cos(yaw90) * speed;
        change.z += glm::sin(yaw90) * speed;
    }

    if (sf::Keyboard::isKeyPressed(KeyBinds::getKey(KeyBinds::Control::Player_Left)))
    {
        change.x -= glm::cos(yaw) * speed;
        change.z -= glm::sin(yaw) * speed;
    }

    if (sf::Keyboard::isKeyPressed(KeyBinds::getKey(KeyBinds::Control::Player_Right)))
    {
        change.x += glm::cos(yaw) * speed;
        change.z += glm::sin(yaw) * speed;
    }

    if (sf::Keyboard::isKeyPressed(KeyBinds::getKey(KeyBinds::Control::Player_Up)))
    {
        if (m_isFlying)
        {
            change.y += speed;
        }
        else if (m_isOnGround)
        {
            change.y += 12;
        }
        else if (m_isInLiquid)
        {
            change.y += 0.5;
        }
    }

    if (sf::Keyboard::isKeyPressed(KeyBinds::getKey(KeyBinds::Control::Player_Down)))
    {
        change.y -= speed;
    }

    m_flyModeToggle.input();

    addForce(change);
}


void Player::mouseInput ()
{
    if (m_mouseLock)
        return;

    static sf::Vector2i lastMousePosition = sf::Mouse::getPosition();

    auto mouseChange = sf::Mouse::getPosition() - lastMousePosition;

    rotation.y += mouseChange.x * 0.05;
    rotation.x += mouseChange.y * 0.05;

    constexpr int8_t BOUND = 82;

    if (rotation.x > BOUND)
    {
        rotation.x = BOUND;
    }
    else if (rotation.x < -BOUND)
    {
        rotation.x = -BOUND;
    }
    if (rotation.y < 0)
    {
        rotation.y = 360;
    }
    else if (rotation.y > 360)
    {
        rotation.y = 0;
    }

    auto centerX = Display::get().getRaw().getSize().x / 4;
    auto centerY = Display::get().getRaw().getSize().y / 4;

    sf::Mouse::setPosition({static_cast<int>(centerX),
                            static_cast<int>(centerY)}, Display::get().getRaw());

    lastMousePosition = sf::Mouse::getPosition();
}
