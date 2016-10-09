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
    setAABB();
    getCurrentChunk();
    //m_camera.move( dt );
    input( dt );
    m_velocity *= 0.98;
    m_camera.movePosition( m_velocity );
}


const Camera& Player :: getCamera () const
{
    return m_camera;
}

void Player :: input ( float dt )
{
    Vector3 velocityChange;

    if  ( sf::Keyboard::isKeyPressed( sf::Keyboard::W ) )
    {
        float angle = glm::radians( m_rotation.y + 90 );
        velocityChange.x -= cos ( angle) * ACC;
        velocityChange.z -= sin ( angle) * ACC;
    }
    if  ( sf::Keyboard::isKeyPressed( sf::Keyboard::D ) )
    {
        float angle = glm::radians( m_rotation.y );
        velocityChange.x += cos ( angle) * ACC;
        velocityChange.z += sin ( angle) * ACC;
    }
    if  ( sf::Keyboard::isKeyPressed( sf::Keyboard::A ) )
    {
        float angle = glm::radians( m_rotation.y );
        velocityChange.x -= cos ( angle) * ACC;
        velocityChange.z -= sin ( angle) * ACC;
    }
    if  ( sf::Keyboard::isKeyPressed( sf::Keyboard::S ) )
    {
        float angle = glm::radians( m_rotation.y + 90 );
        velocityChange.x += cos ( angle) * ACC;
        velocityChange.z += sin ( angle) * ACC;
    }

    velocityChange *= dt;
    m_velocity += velocityChange;
}

void Player :: getCurrentChunk ()
{
    int x = m_camera.getPosition().x / Chunk::WIDTH;
    int z = m_camera.getPosition().z / Chunk::WIDTH;
   // m_currentChunk = &*m_p_chunks->at( { x, z } );
}

void Player :: setAABB ()
{
    float x = m_camera.getPosition().x - 0.15;
    float z = m_camera.getPosition().z - 0.15;
    float y = m_camera.getPosition().x + 0.15;

    m_aabb.setPosition( { x, y, z } );
}




























