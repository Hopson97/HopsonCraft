#include "Player.h"

#include <SFML/Graphics.hpp>

#include <cstdint>

#include "../Maths/General_Maths.h"
#include "../World/Block/D_Blocks.h"
#include "../World/Chunk/Chunk_Map.h"

#include "../Util/Debug_Display.h"
#include "../Util/Display.h"

#include "../Input/Key_Binds.h"

#include "../Maths/Position_Converter_Maths.h"

Player::Player(Chunk_Map& chunkMap)
:   m_p_heldBlock   (&Block::grass)
,   m_p_chunkMap    (&chunkMap)
,   m_chunkLocation (Maths::worldToChunkPosition(position))
{
    position = {20000, 250, 20000};
    Debug_Display::addheldBlock (*m_p_heldBlock);
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
    Debug_Display::addheldBlock (*m_p_heldBlock);
    Debug_Display::addPlayerPosition(position);
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

