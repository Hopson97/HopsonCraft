#include "Chunk_Renderer.h"

#include <iostream>

#include "../World/Chunk/Chunk.h"
#include "../Player/Camera.h"
#include "../Maths/Matrix_Maths.h"
#include "../Util/Display.h"
#include "../D_Settings.h"

void Chunk_Renderer::addChunk (const Chunk& chunk)
{
    m_chunks.push_back( &chunk );
}

void Chunk_Renderer::render(const Camera& camera)
{
    m_shader.useProgram();
    m_shader.loadCameraMatrix(camera);

    m_shader.loadSkyColour  ({Settings::SKY_RED,
                              Settings::SKY_GREEN,
                              Settings::SKY_BLUE
                            });

    glEnable    (GL_CULL_FACE);
    glCullFace  (GL_BACK);

    for (const Chunk* chunk : m_chunks)
    {
        prepareChunk( *chunk );
        glDrawArrays( GL_TRIANGLES, 0, chunk->getMesh().getSolidPart().model.getVertexCount() );
    }

    m_chunks.clear();
    glBindVertexArray ( 0 );
    glUseProgram(0);
}

void Chunk_Renderer::prepareChunk (const Chunk& chunk)
{
    chunk.getMesh().getSolidPart().model.bind();
    m_shader.loadChunkMatrix( Maths::createModelMatrix( { chunk.getPosition().x, 0, chunk.getPosition().y },
                                                        { 0, 0, 0 },
                                                        { 1, 1, 1 } ) );
}
