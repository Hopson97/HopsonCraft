#include "Player.h"

#include <iostream>

#include "../Util/Debug_Display.h"
#include "../World/Block/Block.h"
#include "../World/Block/D_Blocks.h"

Player::Player()
:   m_rotationLock          ([&](){m_isRotLocked = !m_isRotLocked;}, sf::Keyboard::L, 0.5)
,   m_increaseBlockToggle   ([&](){m_canChangeBlock = !m_canChangeBlock;}, sf::Keyboard::Right, 0.2)
,   m_decreaseBlockToggle   ([&](){m_canChangeBlock = !m_canChangeBlock;}, sf::Keyboard::Left,  0.2)
,   m_heldBlock             (&Block::getBlockFromId(Block::ID::Glass))
{
    m_camera.movePosition({20000, 250, 20000});
    Debug_Display::addheldBlock(*m_heldBlock);
}

void Player::input(const sf::Event& e)
{
    movementInput();
    toggleInput(e);
}

void Player::movementInput()
{
    Vector3 velocityChange;
    auto acceleration = sf::Keyboard::isKeyPressed( sf::Keyboard::LControl ) ? ACC * 10 : ACC;

    //Forward/Back/Left/Right

    if  (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        auto yaw    = glm::radians(m_camera.getRotation().y + 90);

        velocityChange.x -= cos (yaw) * acceleration;
        velocityChange.z -= sin (yaw) * acceleration;
    }
    if  (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        auto yaw = glm::radians(m_camera.getRotation().y);
        velocityChange.x += cos (yaw) * acceleration;
        velocityChange.z += sin (yaw) * acceleration;
    }
    if  (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        auto yaw = glm::radians(m_camera.getRotation().y);
        velocityChange.x -= cos (yaw) * acceleration;
        velocityChange.z -= sin (yaw) * acceleration;
    }
    if  (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        auto yaw    = glm::radians(m_camera.getRotation().y + 90);

        velocityChange.x += cos (yaw) * acceleration;
        velocityChange.z += sin (yaw) * acceleration;
    }

    //Up/ Down
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
    {
        velocityChange.y -= acceleration;
    }
    if (sf::Keyboard::isKeyPressed( sf::Keyboard::Space ))
    {
        velocityChange.y += acceleration;
    }
    m_velocity += velocityChange;
}

void Player::toggleInput(const sf::Event& e)
{
    m_rotationLock.checkInput(e);
    if (!m_isRotLocked)
        m_camera.update();

    if (m_increaseBlockToggle.checkInput(e)) switchBlock(1);
    if (m_decreaseBlockToggle.checkInput(e)) switchBlock(-1);
}


void Player::update(float dt, Camera& camera)
{
    m_velocity *= 0.95;
    m_camera.movePosition(m_velocity * dt);
    Debug_Display::addLookVector(m_camera.getRotation());

    auto& pos = m_camera.getPosition();

    if (pos.x <= 0.1 ) m_camera.setPosition({0.1,   pos.y, pos.z});
    if (pos.z <= 0.1 ) m_camera.setPosition({pos.x, pos.y, 0.1});

    camera = m_camera;
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

Block_t& Player::getHeldBlock ()
{
    return *m_heldBlock;
}

void Player::switchBlock(int inc)
{
    constexpr static auto NUM_BLOCK_TYPES = static_cast<int>(Block::ID::NUM_BLOCK_TYPES);

    auto currId = static_cast<int>(m_heldBlock->getID());
    currId += inc;

    //Seeing as "0" is an air block, we just skip over it
    if (currId == 0) currId = NUM_BLOCK_TYPES - 1;
    else if (currId == NUM_BLOCK_TYPES) currId = 1;

    auto* newBlock = &Block::getBlockFromId(static_cast<Block::ID>(currId));

    //We don't want to place liquid and gas as blocks, so skip.
    if (newBlock->getPhysicalState() == Block::Physical_State::Liquid ||
        newBlock->getPhysicalState() == Block::Physical_State::Gas)
    {
        currId += inc;
    }

    m_heldBlock = &Block::getBlockFromId(static_cast<Block::ID>(currId));

    Debug_Display::addheldBlock(*m_heldBlock);
}

void Player::setPosition(const Vector3& position)
{
    m_camera.setPosition(position);
}

void Player::setRotation(const Vector3& rotation)
{
    m_camera.setRotation(rotation);
}














