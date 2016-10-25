#include "Water_Renderer.h"

#include <iostream>

#include "Chunk/Chunk.h"
#include "Camera.h"
#include "Maths/Matrix_Maths.h"
#include "Display.h"
#include "D_Settings.h"

Water_Renderer :: Water_Renderer()
{
    m_shader.start();
    m_shader.loadProjMatrix( Maths::createPerspectiveMatrix() );
    m_shader.stop();
}

void Water_Renderer :: addChunk ( const Chunk& chunk )
{
    m_chunks.push_back( &chunk );
}

void Water_Renderer :: render( const Camera& camera )
{
    m_shader.start();
    m_shader.loadViewMatrix( camera );

    m_shader.loadSkyColour  ( {     Settings::SKY_RED,
                                    Settings::SKY_GREEN,
                                    Settings::SKY_BLUE
                            } );

    glDisable( GL_CULL_FACE );
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
    m_shader.loadModelMatrix( Maths::createModelMatrix( { chunk.getPosition().x, 0, chunk.getPosition().y },
                                                                  { 0, 0, 0 },
                                                                  { 1, 1, 1 } ) );

    m_shader.loadTime( m_timer.getElapsedTime().asSeconds() );
}
