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
,   lastPlayerPos   ( m_player.getChunkLocation() )
{
    sf::Clock clock;

   // std::cout << "Generating block data... (This might take a while)." << std::endl;
    int size = worldSize;
    /*
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
    */
    //std::cout << "Chunk block data created, Time: " << clock.getElapsedTime().asSeconds() << "s\n";

   // m_chunks.at( { 0, 0 } )->generateMesh();
    //m_chunks.at( { 0, 0 } )->bufferMesh();

    std::thread vertexGenThread ( &World::generateChunks, this );
    vertexGenThread.detach();
}

World :: ~World ()
{
    m_isRunning = false;
    std::this_thread::sleep_for( std::chrono::seconds ( 1 ) );
}

void World :: update ( float dt )
{
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
    m_chunks[ location ] = std::make_unique<Chunk> ( m_chunks, location, m_blockAtlas );
    m_chunks[ location ]->generateStructureData();
}



void World :: generateChunks ()
{
    while ( m_isRunning )
    {
        int minX =  m_player.getChunkLocation().x - renderDistance;
        int minZ =  m_player.getChunkLocation().z - renderDistance;

        int maxX =  m_player.getChunkLocation().x + renderDistance;
        int maxZ =  m_player.getChunkLocation().z + renderDistance;


        for ( int x = minX ; x < maxX ; x++ )
        {
            for ( int z = minZ ; z < maxZ ; z++ )
            {
                if ( m_chunks.find( { x, z } ) == m_chunks.end() )
                {
                    addChunk( {x, z } );
                }
            }
        }

        for ( auto itr = m_chunks.begin() ; itr != m_chunks.end() ; )
        {
            Chunk&      currChunk   = *(*itr).second;
            Vector2i    loc         = currChunk.getLocation();

            if ( loc.x < minX || loc.x > maxX || loc.z < minZ || loc.z > maxZ )
            {
                itr = m_chunks.erase( itr );
            }
            else
            {
                if ( !currChunk.hasVertexData() && currChunk.hasBlockData() )
                {
                    currChunk.generateMesh();
                }
                itr++;
            }
        }








    }

/*
    for ( int x = 0 ; x < World::worldSize ; x++ )
    {
        for ( int z = 0 ; z < World::worldSize ; z++ )
        {
            Chunk& chunk = *m_chunks.at( { x, z } );

            if ( chunk.hasBlockData() && !chunk.hasVertexData() )
            {
                chunk.generateMesh();
            }
        }
    }
*/
}

