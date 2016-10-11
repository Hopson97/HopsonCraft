#include "Player.h"

#include <SFML/Graphics.hpp>

#include <iostream>
Player :: Player( std::unordered_map<Vector2i, Chunk_Ptr>& chunkMap )
:   m_p_chunks  ( &chunkMap )
,   m_aabb      (  { 0.3, 0.3, 1.7 } )
{
    m_camera.movePosition( { Chunk::WIDTH * 16 / 2, 80, Chunk::WIDTH * 16 / 2 } );
}

void Player :: update ( float dt )
{
    input( dt );

    setAABB();
    getCurrentChunk();
    if ( !m_isLocked ) m_camera.update();

    m_velocity *= 0.98;
    m_camera.movePosition( m_velocity );
}


const Camera& Player :: getCamera () const
{
    return m_camera;
}

const Vector2i& Player :: getChunkLocation () const
{
    return m_currentChunk->getLocation();
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

    velocityChange *= dt;
    m_velocity += velocityChange;
}

void Player :: getCurrentChunk ()
{
    int x = m_camera.getPosition().x / Chunk::WIDTH;
    int z = m_camera.getPosition().z / Chunk::WIDTH;
    if ( m_p_chunks->find( { x, z } ) != m_p_chunks->end() )
    {
        m_currentChunk = &*m_p_chunks->at( { x, z } );
    }
}

void Player :: setAABB ()
{
    float x = m_camera.getPosition().x - 0.15;
    float z = m_camera.getPosition().z - 0.15;
    float y = m_camera.getPosition().x + 0.15;

    m_aabb.setPosition( { x, y, z } );
}




























