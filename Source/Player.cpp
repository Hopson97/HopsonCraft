#include "Player.h"


void Player::update(float dt)
{
    input(dt);
    m_velocity *= 0.95;
    m_camera.movePosition(m_velocity * dt);
    m_camera.update();
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

void Player::input(float dt)
{
    Vector3 velocityChange;

    auto acceleration = sf::Keyboard::isKeyPressed( sf::Keyboard::LControl ) ? ACC * 4 : ACC;

    if  (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        auto angle = glm::radians(m_camera.getRotation().y + 90);
        velocityChange.x -= cos (angle) * acceleration;
        velocityChange.z -= sin (angle) * acceleration;
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
        auto angle = glm::radians(m_camera.getRotation().y + 90);
        velocityChange.x += cos (angle) * acceleration;
        velocityChange.z += sin (angle) * acceleration;
    }

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
