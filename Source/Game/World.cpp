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

World::World()
:   m_blockAtlas    ( 512, 16, "Blocks_Sonic" )
,   m_player        ( m_chunks )
{
    sf::Clock clock;

    World::worldSize = 10;

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
    m_isRunning = false;
}

void World :: update ( float dt )
{
    m_player.update( dt );

    Block::ID id = static_cast<Block::ID>(Random::integer( 0, static_cast<int>( Block::ID::NUM_BLOCK_TYPES ) ) );
    static sf::Clock c;
    if ( c.getElapsedTime().asSeconds() > 1 )
    {
        m_chunks.at( { 0, 0 } )->setBlock ( 0, 0, 0, id, true );
        c.restart();
    }
}

void World :: draw ()
{
    for ( auto& chunk : m_chunks )
    {
        if ( chunk.second->hasBuffered() )
        {
            m_chunkRenderer.renderChunk( *chunk.second );
        }
        else if ( chunk.second->hasVertexData())
        {
            chunk.second->bufferMesh();
        }
    }

    m_chunkRenderer.render( m_player.getCamera(), m_player.getChunkLocation() );
}




void World :: addChunk ( const Vector2i& location )
{
    m_chunks[ location ] = std::make_unique<Chunk> ( m_chunks, location, m_blockAtlas );
}

