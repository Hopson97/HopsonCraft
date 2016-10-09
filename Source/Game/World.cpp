#include "World.h"

#include "Shader_Loader.h"

#include "Window.h"
#include "Loader.h"
#include "Application.h"
#include "Height_Generator.h"

#include <iostream>


World::World()
:   m_blockAtlas    ( 512, 16 )
,   m_player        ( m_chunks )
{
    //Height_Generator::setUp( 210, 0.5, 4, -1 );   //Hilly
    Height_Generator::setUp( 220, 0.4, 4, -1 );   //Very watery
    //Height_Generator::setUp( 250, 0.4, 5, -1 );   //Very hilly
    //Height_Generator::setUp( 150, 0.6, 4, -1 );   //Ocean

    m_blockAtlas.loadFromFile( "Blocks_Sonic" );

    int size = 12;
    for ( int x = 0 ; x < size ; x++ )
    {
        for ( int z = 0 ; z < size ; z++ )
        {
            addChunk( { x, z } );
        }
    }

    for ( auto& chunk : m_chunks )
    {
        chunk.second->generateMesh();
    }
}

void World :: update ( float dt )
{
    m_player.update( dt );
}

void World :: draw ()
{
    for ( auto& chunk : m_chunks )
    {
        m_chunkRenderer.renderChunk( *chunk.second );
    }
    m_chunkRenderer.render( m_player.getCamera() );
}




void World :: addChunk ( const Vector2i& location )
{
    m_chunks[ location ] = std::make_unique<Chunk> ( &m_chunks, location, m_blockAtlas );
}
