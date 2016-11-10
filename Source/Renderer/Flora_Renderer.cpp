#include "Flora_Renderer.h"

#include "Chunk/Chunk.h"
#include "Camera.h"
#include "Maths/Matrix_Maths.h"
#include "Display.h"
#include "D_Settings.h"

#include <iostream>

void Flora_Renderer::addChunk (const Chunk& chunk)
{
    m_chunks.push_back( &chunk );
}

void Flora_Renderer::render(const Camera& camera)
{
    m_shader.useProgram();
    m_shader.loadCameraMatrix(camera);

    m_shader.loadSkyColour  ({Settings::SKY_RED,
                              Settings::SKY_GREEN,
                              Settings::SKY_BLUE
                            });

    glDisable   (GL_CULL_FACE);

    for (const Chunk* chunk : m_chunks)
    {
        prepareChunk( *chunk );
        glDrawArrays( GL_TRIANGLES, 0, chunk->getMesh().getFloraPart().model.getVertexCount());
    }

    m_chunks.clear();
    glBindVertexArray ( 0 );
    glUseProgram(0);
}

void Flora_Renderer::prepareChunk (const Chunk& chunk)
{
    chunk.getMesh().getFloraPart().model.bind();
    m_shader.loadChunkMatrix( Maths::createModelMatrix( { chunk.getPosition().x, 0, chunk.getPosition().y },
                                                        { 0, 0, 0 },
                                                        { 1, 1, 1 } ) );
}
