#include "Player.h"

Player::Player()
:   m_rotationLock ([&](){m_isRotLocked = !m_isRotLocked;}, sf::Keyboard::L, 0.5)
{
    m_camera.movePosition({100, 140, 100});
}

void Player::input()
{
    m_rotationLock.checkInput();
    if (!m_isRotLocked)
        m_camera.update();

    Vector3 velocityChange;
    auto acceleration = sf::Keyboard::isKeyPressed( sf::Keyboard::LControl ) ? ACC * 4 : ACC / 2;

    //Forward/Back/Left/Right
    if  (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        auto yaw    = glm::radians(m_camera.getRotation().y + 90);
        auto pitch  = glm::radians(m_camera.getRotation().x);

        velocityChange.x -= cos (yaw)   * acceleration;
        velocityChange.z -= sin (yaw)   * acceleration;
        velocityChange.y -= sin (pitch) * acceleration;
    }
    if  (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        auto angle = glm::radians(m_camera.getRotation().y);
        velocityChange.x += cos (angle) * acceleration;
        velocityChange.z += sin (angle) * acceleration;
    }
    if  (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        auto angle = glm::radians(m_camera.getRotation().y);
        velocityChange.x -= cos (angle) * acceleration;
        velocityChange.z -= sin (angle) * acceleration;
    }
    if  (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        auto yaw    = glm::radians(m_camera.getRotation().y + 90);
        auto pitch  = glm::radians(m_camera.getRotation().x);

        velocityChange.x += cos (yaw)   * acceleration;
        velocityChange.z += sin (yaw)   * acceleration;
        velocityChange.y += sin (pitch) * acceleration;
    }

    //Up/ Down
    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::LShift ) )
    {
        velocityChange.y -= acceleration;
    }
    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Space ) )
    {
        velocityChange.y += acceleration;
    }





    m_velocity += velocityChange;
}

void Player::update(float dt)
{
    m_velocity *= 0.95;
    m_camera.movePosition(m_velocity * dt);
}

const Camera& Player::getCamera() const
{
    return m_camera;
}

const Vector3& Player::getPosition() const
{
    return m_camera.getPosition();
}

const Vector3& Player::getRotation() const
{
    return m_camera.getRotation();
}

