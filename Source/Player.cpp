#include "Player.h"

#include <iostream>

#include "Block/D_Blocks.h"

Player::Player()
:   m_rotationLock          ([&](){m_isRotLocked = !m_isRotLocked;}, sf::Keyboard::L, 0.5)
,   m_increaseBlockToggle   ([&](){m_canChangeBlock = !m_canChangeBlock;}, sf::Keyboard::Right, 0.2)
,   m_decreaseBlockToggle   ([&](){m_canChangeBlock = !m_canChangeBlock;}, sf::Keyboard::Left,  0.2)
,   m_heldBlock             (&Block::grass)
{
    m_camera.movePosition({500, 145, 500});
}

void Player::input()
{
    m_rotationLock.checkInput();
    if (!m_isRotLocked)
        m_camera.update();

    if (m_increaseBlockToggle.checkInput()) switchBlock(1);
    if (m_decreaseBlockToggle.checkInput()) switchBlock(-1);

    Vector3 velocityChange;
    auto acceleration = sf::Keyboard::isKeyPressed( sf::Keyboard::LControl ) ? ACC * 4 : ACC / 2;

    //Forward/Back/Left/Right
    if  (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        auto yaw    = glm::radians(m_camera.getRotation().y + 90);
        auto pitch  = glm::radians(m_camera.getRotation().x);

        velocityChange.x -= cos (yaw) * acceleration;
        velocityChange.z -= sin (yaw) * acceleration;

        //velocityChange.x -= cos (yaw)   * acceleration;
        //velocityChange.z -= sin (yaw)   * acceleration;
        //velocityChange.y -= tan (pitch) * acceleration;
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

        velocityChange.x += cos (yaw) * acceleration;
        velocityChange.z += sin (yaw) * acceleration;

        //velocityChange.x += cos (yaw)   * acceleration;
        //velocityChange.z += sin (yaw)   * acceleration;
        //velocityChange.y += tan (pitch) * acceleration;
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

Block::Block_Base& Player::getHeldBlock ()
{
    return *m_heldBlock;
}



void Player::switchBlock(int inc)
{
    constexpr static auto NUM_BLOCK_TYPES = static_cast<int>(Block::ID::NUM_BLOCK_TYPES);

    auto currId = static_cast<int>(m_heldBlock->getID());
    currId += inc;

    //We don't want to place water, so skip over it!
    if (static_cast<Block::ID>(currId) == Block::water.getID())
    {
        currId += inc;
    }

    //Seeing as "0" is an air block, we just skip over it
    if (currId == 0) currId = NUM_BLOCK_TYPES - 1;
    else if (currId == NUM_BLOCK_TYPES) currId = 1;



    std::cout << "Switching to block id: " << currId << std::endl;

    m_heldBlock = &Block::getBlock(static_cast<Block::ID>(currId));
}















