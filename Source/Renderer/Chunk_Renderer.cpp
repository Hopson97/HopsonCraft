#include "Chunk_Renderer.h"

#include "Chunk.h"
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

void Chunk_Renderer :: render( const Camera& camera )
{
    m_shader.start();
    m_shader.loadViewMatrix( camera );

    for ( const Chunk* chunk : m_chunks )
    {
        prepareChunk( *chunk );
        glDrawArrays( GL_TRIANGLES, 0, chunk->getModel().getVertexCount() );
    }
    m_chunks.clear();
    glBindVertexArray ( 0 );
    m_shader.stop();
}

void Chunk_Renderer :: prepareChunk ( const Chunk& chunk )
{
    chunk.getModel().bind();
    m_shader.loadModelMatrix( Maths::createTransforrmationMatrix( chunk.position,
                                                                  chunk.rotation,
                                                                  chunk.scale ) );
}
