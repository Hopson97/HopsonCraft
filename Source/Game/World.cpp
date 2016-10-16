#include "World.h"

#include <thread>

#include "Shader_Loader.h"

#include "Window.h"
#include "Loader.h"
#include "Application.h"
#include "Height_Generator.h"
#include "Random.h"

#include <iostream>

World::World()
:   m_blockAtlas    ( 512, 16, "Blocks_Sonic" )
,   m_player        ( m_chunks )
,   lastPlayerPos   ( m_player.getChunkLocation() )
{
    sf::Clock clock;

    addChunk( { 0, 0 } );
    m_chunks.at( { 0, 0 } )->generateMesh();
    m_chunks.at( { 0, 0 } )->bufferMesh();

    std::thread ( &World::manageChunks, this ).detach();
}

World :: ~World ()
{
    m_isRunning = false;
    std::this_thread::sleep_for( std::chrono::seconds ( 1 ) );
}

void World :: update ( float dt )
{
    for ( auto itr = m_chunks.begin() ; itr != m_chunks.end() ; )
    {
        Chunk&      currChunk   = *(*itr).second;

        if ( currChunk.shouldBeDeleted() )
        {
            itr = m_chunks.erase( itr );
        }
        else itr++;
    }


    m_player.update( dt );
    updateChunks();
}

void World :: draw ()
{
    int calls = 0;
    for ( auto itr = m_chunks.begin() ; itr != m_chunks.end() ; )
    {
        if ( itr->second->hasBuffered() )
        {

            m_renderer.processChunk( *itr->second );
            itr++;
            calls++;
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
    m_chunkAddMutex.lock();
    if ( m_chunks.find( location) == m_chunks.end() )
    {
        m_chunks[ location ] = std::make_unique<Chunk> ( m_chunks, location, m_blockAtlas, *this );
    }
    m_chunkAddMutex.unlock();
}


//This below is all ran on a seperate thread
struct RenderArea
{
    int minX;
    int minZ;

    int maxX;
    int maxZ;
};


void World :: manageChunks()
{
    while ( m_isRunning )
    {
        RenderArea area;
        area.minX =  m_player.getChunkLocation().x - m_loadDistance;
        area.minZ =  m_player.getChunkLocation().z - m_loadDistance;

        area.maxX =  m_player.getChunkLocation().x + m_loadDistance;
        area.maxZ =  m_player.getChunkLocation().z + m_loadDistance;

        generateChunks( area );

        if ( m_loadDistance < m_renderDistance )
        {
            m_loadDistance++;
        }
        else if ( m_loadDistance > m_renderDistance )
        {
            m_loadDistance = m_renderDistance;
        }

        if ( !m_isRunning ) return;

        checkChunks( area );
    }
}

void World :: generateChunks ( const RenderArea& area )
{
    std::vector<std::unique_ptr<std::thread>> threads;

    for ( int x = area.minX ; x < area.maxX ; x++ )
    {
        for ( int z = area.minZ ; z < area.maxZ ; z++ )
        {
            if ( !m_isRunning ) return; //Safety
            if ( m_chunks.find( { x, z } ) == m_chunks.end() )
            {
                addChunk( {x, z } );
            }
        }
        for ( auto& thread : threads ) thread->join();
        threads.clear();

    }
}

void World::checkChunks( const RenderArea& area )
{
    for ( auto& chunkPair : m_chunks )
    {
        Chunk& chunk = *chunkPair.second;
        Vector2i loc = chunk.getLocation();
        if ( loc.x < area.minX ||
             loc.x > area.maxX ||
             loc.z < area.minZ ||
             loc.z > area.maxZ )
        {
            chunk.setToDelete();
        }
        else
        {
            if ( !chunk.hasVertexData() && chunk.hasBlockData() )
            {
                chunk.generateMesh();
            }
        }

    }
}


