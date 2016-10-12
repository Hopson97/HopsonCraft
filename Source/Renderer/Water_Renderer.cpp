#include "Water_Renderer.h"

#include <iostream>

#include "Chunk/Chunk.h"
#include "Camera.h"
#include "Maths.h"
#include "Window.h"

Water_Renderer :: Water_Renderer()
{
    m_shader.start();
    m_shader.loadProjMatrix( glm::perspective( glm::radians( 75.0f ),
                                               Window::getAspect(),
                                               0.01f,
                                               1000.0f ) );
    m_shader.stop();
}

void Water_Renderer :: addChunk ( const Chunk& chunk )
{
    m_chunks.push_back( &chunk );
}

void Water_Renderer :: render( const Camera& camera )
{
    //glDisable( GL_CULL_FACE );

    m_shader.start();
    m_shader.loadViewMatrix( camera );

    for ( const Chunk* chunk : m_chunks )
    {
        prepareWater( *chunk );

        glDrawArrays( GL_TRIANGLES, 0, chunk->getWaterModel().getVertexCount() );
    }

    m_chunks.clear();
    glBindVertexArray ( 0 );
    m_shader.stop();
}

void Water_Renderer :: prepareWater ( const Chunk& chunk )
{
    chunk.getWaterModel().bind();
    m_shader.loadModelMatrix( Maths::createTransforrmationMatrix( { chunk.getPosition().x, 0, chunk.getPosition().y },
                                                                  { 0, 0, 0 },
                                                                  { 1, 1, 1 } ) );

    m_shader.loadTime( m_timer.getElapsedTime().asSeconds() );
}
