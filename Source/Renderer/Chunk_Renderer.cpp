#include "Chunk_Renderer.h"

#include <iostream>

#include "Chunk/Chunk.h"
#include "Camera.h"
#include "Maths.h"
#include "Window.h"

Chunk_Renderer :: Chunk_Renderer ()
{
    m_shader.start();
    m_shader.loadProjMatrix( glm::perspective( glm::radians( 75.0f ),
                                               Window::getAspect(),
                                               0.01f,
                                               1000.0f ) );
    m_shader.stop();
}

void Chunk_Renderer :: renderChunk ( const Chunk& chunk )
{
    m_chunks.push_back( &chunk );
}

void Chunk_Renderer :: render( const Camera& camera, const Vector2i& playerLocation )
{
    m_shader.start();
    m_shader.loadViewMatrix( camera );

    for ( const Chunk* chunk : m_chunks )
    {
        prepareChunk( *chunk );
/*
        if ( playerLocation == chunk->getLocation() )
        {
            m_shader.loadIsPlayerLocation( 1 );
        }
        else
        {
            m_shader.loadIsPlayerLocation( 0 );
        }
*/
        glDrawArrays( GL_TRIANGLES, 0, chunk->getModel().getVertexCount() );
    }

    m_chunks.clear();
    glBindVertexArray ( 0 );
    m_shader.stop();
}

void Chunk_Renderer :: prepareChunk ( const Chunk& chunk )
{
    chunk.getModel().bind();
    m_shader.loadModelMatrix( Maths::createTransforrmationMatrix( { chunk.getPosition().x, 0, chunk.getPosition().y },
                                                                  { 0, 0, 0 },
                                                                  { 1, 1, 1 } ) );
}
