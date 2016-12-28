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

void Player::input()
{
    m_velocity += m_camera.keyboardInput(SPEED);
    m_camera.mouseInput();
}

void Player::update(float dt, Camera& camera, Chunk_Map& chunkMap)
{
    if (!m_isOnGround)
        m_velocity.y -= 10 * dt;

    collision(chunkMap, dt);
    m_camera.position += m_velocity * dt;

    m_velocity *= 0.95;
    camera = m_camera;

    Debug_Display::addLookVector(camera.rotation);
    Debug_Display::addheldBlock (*m_p_heldBlock);
}


const Block::Block_Type& Player::getBlock() const
{
    return *m_p_heldBlock;
}

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

