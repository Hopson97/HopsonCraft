#include "World.h"

#include <thread>

#include "Shader_Loader.h"

#include "Window.h"
#include "Loader.h"
#include "Application.h"
#include "Height_Generator.h"
#include "Random.h"

#include <iostream>

int World :: worldSize = 0;

World::World()
:   m_blockAtlas    ( 512, 16, "Blocks_Sonic" )
,   m_player        ( m_chunks )
{
    sf::Clock clock;

    std::cout << "Generating block data... (This might take a while)." << std::endl;
    int size = worldSize;
    for ( int x = 0 ; x < size ; x++ )
    {
        for ( int z = 0 ; z < size ; z++ )
        {
            addChunk( { x, z } );
        }
    }
    for ( auto& chunk : m_chunks )
    {
        chunk.second->generateStructureData();
    }
    std::cout << "Chunk block data created, Time: " << clock.getElapsedTime().asSeconds() << "s\n";

    m_chunks.at( { 0, 0 } )->generateMesh();
    m_chunks.at( { 0, 0 } )->bufferMesh();

    std::thread vertexGenThread ( &World::manageChunks, this );
    vertexGenThread.detach();
}

World :: ~World ()
{
    m_isRunning = false;    //Basically guarentees the termination of the chunk handling thread.
}

void World :: update ( float dt )
{
    m_player.update( dt );

    Block::ID id = static_cast<Block::ID>(Random::integer( 0, static_cast<int>( Block::ID::NUM_BLOCK_TYPES ) ) );
    static sf::Clock c;
    if ( c.getElapsedTime().asSeconds() > 2 )
    {
        m_chunks.at( { 0, 0 } )->setBlock ( 0, Chunk::HEIGHT - 1, 0, id, true );
        m_updateChunks.push_back( m_chunks.at( { 0, 0 } ).get() );
        c.restart();
    }

    updateChunks();
}

void World :: draw ()
{
    for ( auto itr = m_chunks.begin() ; itr != m_chunks.end() ; )
    {
        if ( itr->second->hasBuffered() )
        {

            m_renderer.processChunk( *itr->second );
            itr++;
        }
        else if ( itr->second->hasVertexData())
        {
            itr->second->bufferMesh();
            itr++;
        }
        else
        {
            itr++;
        }

    }

    m_renderer.render( m_player.getCamera() );
}

void World :: updateChunks ()
{
    for ( auto itr = m_updateChunks.begin() ; itr != m_updateChunks.end() ; )
    {
        (*itr)->generateMesh();
        itr = m_updateChunks.erase( itr );
    }
}



void World :: addChunk ( const Vector2i& location )
{
    m_chunks[ location ] = std::make_unique<Chunk> ( m_chunks, location, m_blockAtlas );
}


void World :: manageChunks ()
{
    std::cout << "Thread launched." << std::endl;
    while ( m_isRunning )
    {
        for ( auto& chunk: m_chunks )
        {
            if ( chunk.second->hasBlockData() && !chunk.second->hasVertexData() )
            {
                //std::cout << "Creating mesh" << std::endl;
                chunk.second->generateMesh();
            }
        }
    }
    std::cout << "Thread terminated." << std::endl;
}

