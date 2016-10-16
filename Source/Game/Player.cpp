#include "Player.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include "World.h"

Player :: Player( std::unordered_map<Vector2i, Chunk_Ptr>& chunkMap )
:   m_p_chunks      ( &chunkMap )
,   m_bottomAABB    ( { 0.3, 0, 0.3 } )
{
    m_camera.movePosition( { 1,  Chunk::HEIGHT - 1, 1 } );
}

void Player :: update ( float dt )
{
    input( dt );

    getCurrentChunk();

    if ( !m_isLocked ) m_camera.update();
    m_velocity *= 0.95;
    m_camera.movePosition( m_velocity * dt );
}


const Camera& Player :: getCamera () const
{
    return m_camera;
}

Vector2i Player :: getChunkLocation () const
{
    int x = m_camera.getPosition().x / Chunk::WIDTH;
    int z = m_camera.getPosition().z / Chunk::WIDTH;
    return { x, z };
}

const Vector3 Player :: getBlockPositionInChunk() const
{
    float x = (int)m_camera.getPosition().x % 16;
    float z = (int)m_camera.getPosition().z % 16;

    return { x, m_camera.getPosition().y, z };
}


void Player :: input ( float dt )
{
    if ( m_lockTimer.getElapsedTime().asSeconds() > 3.0 )
    {
        if ( sf::Keyboard::isKeyPressed( sf::Keyboard::L )) {
            m_lockTimer.restart();
            m_isLocked = !m_isLocked;
        }
    }


    Vector3 velocityChange;

    float acceleration = sf::Keyboard::isKeyPressed( sf::Keyboard::LControl ) ? ACC * 5 : ACC;

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
    int x = m_camera.getPosition().x / Chunk::WIDTH;
    int z = m_camera.getPosition().z / Chunk::WIDTH;
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



























