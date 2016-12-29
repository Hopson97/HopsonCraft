#include "Player.h"

#include <SFML/Graphics.hpp>

#include <cstdint>
#include <iostream>

#include "../Maths/General_Maths.h"
#include "../World/Block/D_Blocks.h"
#include "../World/Chunk/Chunk_Map.h"

#include "../Util/Debug_Display.h"
#include "../Util/Display.h"

#include "../Input/Key_Binds.h"

#include "../Maths/Position_Converter_Maths.h"

Player::Player(Chunk_Map& chunkMap)
:   m_heldBlock     ((uint8_t)Block::ID::Grass)
,   m_p_chunkMap    (&chunkMap)
,   m_chunkLocation (Maths::worldToChunkPosition(position))
{
    position = {20000, 250, 20000};
}

const Chunk_Location& Player::getChunkLocation() const
{
    return m_chunkLocation;
}

void Player::setPosition(const Vector3& position)
{
    this->position = position;
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

void Player::input(Camera& camera)
{
    addForce(camera.keyboardInput(SPEED));
    camera.mouseInput();

    //hax
    camera.position = position;
    rotation = camera.rotation;
}

void Player::onUpdate(float dt)
{
    m_chunkLocation = Maths::worldToChunkPosition(position);

    Debug_Display::addLookVector(rotation);
    Debug_Display::addPlayerPosition(position);
}


const Block::Block_Type& Player::getBlock() const
{
    return Block::get(m_heldBlock);
}

void Player::changeBlock(int increment)
{
    constexpr static auto BLOCK_TYPES = (uint32_t)(Block::ID::NUM_BLOCK_TYPES);

    m_heldBlock += increment;

    //Seeing as "0" is an air block, we just skip over it
    if (m_heldBlock == 0)
        m_heldBlock = BLOCK_TYPES - 1;
    else if (m_heldBlock == BLOCK_TYPES)
        m_heldBlock = 1;

    auto* newBlock = &Block::get(m_heldBlock);

    //We don't want to place liquid and gas as blocks, so skip.
    while ( newBlock->getData().getPhysicalState() == Block::Physical_State::Liquid ||
            newBlock->getData().getPhysicalState() == Block::Physical_State::Gas)
    {
        //std::cout << std::cout << m_heldBlock << std::endl;
        m_heldBlock += increment;
        newBlock = &Block::get(m_heldBlock);
    }

    Debug_Display::addheldBlock (Block::get(m_heldBlock));
}

