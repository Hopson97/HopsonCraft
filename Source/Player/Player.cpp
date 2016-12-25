#include "Player.h"

#include <SFML/Graphics.hpp>

#include <cstdint>

#include "../Maths/General_Maths.h"
#include "../World/Block/D_Blocks.h"
#include "../World/Chunk/Chunk_Map.h"

#include "../Util/Debug_Display.h"
#include "../Util/Display.h"

#include "../Input/Key_Binds.h"

Player::Player()
:   m_p_heldBlock (&Block::grass)
{
    m_camera.position = {20000, 250, 20000};
    Debug_Display::addheldBlock (*m_p_heldBlock);
}


/**

*/
const Camera& Player::getCamera() const
{
    return m_camera;
}


/**

*/
void Player::setPosition(const Vector3& position)
{
    m_camera.position = position;
}


/**

*/
void Player::input (const sf::Event& e)
{
    if (e.type == sf::Event::KeyPressed)
    {
        if (e.key.code == sf::Keyboard::Left)
            changeBlock(-1);
        if (e.key.code == sf::Keyboard::Right)
            changeBlock(1);
    }
}


/**

*/
void Player::input()
{
    translationInput ();
    m_camera.mouseInput();
}


/**

*/
void Player::update(float dt, Camera& camera, Chunk_Map& chunkMap)
{
    if (!m_isOnGround)
        m_velocity.y -= 10 * dt;
   // m_isOnGround = false;

    collision(chunkMap, dt);
    m_camera.position += m_velocity * dt;

    m_velocity *= 0.95;
    camera = m_camera;

    Debug_Display::addLookVector(camera.rotation);
    Debug_Display::addheldBlock (*m_p_heldBlock);
}


/**

*/
const Block::Block_Type& Player::getBlock() const
{
    return *m_p_heldBlock;
}


/**

*/
void Player::translationInput()
{
    Vector3 change;
    auto yaw = glm::radians (m_camera.rotation.y);

    walkingInput(change, yaw);
    upDownInput(change);

    m_velocity += change;
}


/**

*/
void Player::walkingInput(Vector3& change, float yaw)
{
    //Speed variables
    float acc;
    sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) ?
        acc = SPEED * 10 :
        acc = SPEED;

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
}


/**

*/
void Player::upDownInput(Vector3& change)
{
    //Speed variables
    float acc;
    sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) ?
        acc = SPEED * 10 :
        acc = SPEED;

    //Up/ Down
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
    {
        change.y -= acc;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_isOnGround)
    {
        change.y += acc;
        //m_isOnGround = false;
    }
}

/**
    Tempory way of switching blocks I guess
*/
void Player::changeBlock(int increment)
{
    constexpr static auto BLOCK_TYPES = (uint32_t)(Block::ID::NUM_BLOCK_TYPES);

    auto currId = (uint32_t)(m_p_heldBlock->getData().getID());
    currId += increment;

    //Seeing as "0" is an air block, we just skip over it
    if (currId == 0) currId = BLOCK_TYPES - 1;
    else if (currId == BLOCK_TYPES) currId = 1;

    auto* newBlock = &Block::get(static_cast<Block::ID>(currId));

    //We don't want to place liquid and gas as blocks, so skip.
    if (newBlock->getData().getPhysicalState() == Block::Physical_State::Liquid ||
        newBlock->getData().getPhysicalState() == Block::Physical_State::Gas)
    {
        currId += increment;
    }

    m_p_heldBlock = &Block::get(static_cast<Block::ID>(currId));
}

#include <iostream>
/**

*/
void Player::collision(Chunk_Map& chunkMap, float dt)
{
/*
    static auto width     = 0.3;
    static auto height    = 1.5;
    auto pos = m_camera.position + m_velocity;
*/
}










