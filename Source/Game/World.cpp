#include "World.h"

#include "Shader_Loader.h"

#include "Window.h"
#include "Loader.h"
#include "Application.h"
#include "Height_Generator.h"

#include <iostream>


World::World()
:   m_blockAtlas    ( 512, 16 )
{
    Height_Generator::setUp( 210, 0.5, 4, -1 );

    m_blockAtlas.loadFromFile( "Blocks" );

    int size = 16;
    for ( int x = 0 ; x < size ; x++ )
    {
        for ( int z = 0 ; z < size ; z++ )
        {
            addChunk( { x, z } );
        }
    }

    m_camera.movePosition( { 0, Chunk::maxHeight, 10 } );

    for ( auto& chunk : m_chunks )
    {
        chunk.second->generateMesh();
    }
}

void World :: update ( float dt )
{
    m_camera.move( dt );
}

void World :: draw ()
{
    for ( auto& chunk : m_chunks )
    {
        m_chunkRenderer.renderChunk( *chunk.second );
    }
    m_chunkRenderer.render( m_camera );
}




void World :: addChunk ( const Vector2i& location )
{
    m_chunks[ location ] = std::make_unique<Chunk> ( &m_chunks, location, m_blockAtlas );
}
