#include "Player.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include "World.h"

Player :: Player( std::unordered_map<Chunk_Location, Chunk_Ptr>& chunkMap )
:   m_p_chunks      ( &chunkMap )
,   m_bottomAABB    ( { 0.3, 0, 0.3 } )
{
    m_camera.movePosition( { 0,  Chunk::WATER_LEVEL + 25, 0 } );

    m_toggles.emplace_back( [&]() { m_isLocked  = !m_isLocked;  }, sf::Keyboard::L, 3.0f );
    m_toggles.emplace_back( [&]() { m_isFlyMode = !m_isFlyMode; }, sf::Keyboard::F, 1.0f );
}

void Player :: update ( float dt )
{
    input( dt );

    getCurrentChunk();

    if ( !m_isLocked ) m_camera.update();
    m_velocity *= 0.95;

    if ( !m_isFlyMode )
    {
        m_velocity.y -= 0.8;
    }
    m_camera.movePosition( m_velocity * dt );
/*
    if (m_camera.getPosition().y > 125 )
    {
        m_velocity.y -= 0.8;
    }
    else
    {
        m_velocity.y = 0;
    }*/
}


const Camera& Player :: getCamera () const
{
    return m_camera;
}

const Vector3& Player :: getPosition () const
{
    return m_camera.getPosition();
}

const Vector3&  Player :: getRotation () const
{
    return m_camera.getRotation();
}

void Player :: input ( float dt )
{
    for ( auto& toggle : m_toggles )
    {
        toggle.checkInput();
    }

    Vector3 velocityChange;

    float acceleration = sf::Keyboard::isKeyPressed( sf::Keyboard::LControl ) ? ACC * 4 : ACC;

    if  ( sf::Keyboard::isKeyPressed( sf::Keyboard::W ) )
    {
        float angle = glm::radians( m_camera.getRotation().y + 90 );
        velocityChange.x -= cos ( angle) * acceleration;
        velocityChange.z -= sin ( angle) * acceleration;
    }
    if  ( sf::Keyboard::isKeyPressed( sf::Keyboard::D ) )
    {
        float angle = glm::radians( m_camera.getRotation().y );
        velocityChange.x += cos ( angle) * acceleration;
        velocityChange.z += sin ( angle) * acceleration;
    }
    if  ( sf::Keyboard::isKeyPressed( sf::Keyboard::A ) )
    {
        float angle = glm::radians( m_camera.getRotation().y );
        velocityChange.x -= cos ( angle) * acceleration;
        velocityChange.z -= sin ( angle) * acceleration;
    }
    if  ( sf::Keyboard::isKeyPressed( sf::Keyboard::S ) )
    {
        float angle = glm::radians( m_camera.getRotation().y + 90 );
        velocityChange.x += cos ( angle) * acceleration;
        velocityChange.z += sin ( angle) * acceleration;
    }
    if  ( sf::Keyboard::isKeyPressed( sf::Keyboard::Space ) && m_velocity.y == 0 )
    {
        //m_velocity.y += 40;
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

void Player :: getCurrentChunk ()
{
    int x = m_camera.getPosition().x / Chunk::SIZE;
    int z = m_camera.getPosition().z / Chunk::SIZE;
    if ( m_p_chunks->find( { x, z } ) != m_p_chunks->end() )
    {
        m_p_currentChunk = &*m_p_chunks->at( { x, z } );
    }
}

void Player :: setAABB ()
{
    float x = m_camera.getPosition().x - 0.15;
    float z = m_camera.getPosition().z - 0.15;
    float y = m_camera.getPosition().y - 0.5;

    m_bottomAABB.setPosition( { x, y, z } );

}

void Player :: collide ()
{
    //Down
    {
        Vector3 pointBL ( m_bottomAABB.minX,
                          m_bottomAABB.minY,
                          m_bottomAABB.minZ );
        if ( Collision::pointInAABB( pointBL, m_p_currentChunk->getBlockAABBTop( pointBL )) ) m_velocity.y = 0;
    }

}



























