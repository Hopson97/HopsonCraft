#include "Water_Renderer.h"

#include <iostream>

#include "../World/Chunk/Chunk.h"
#include "../Player/Camera.h"
#include "../Maths/Matrix_Maths.h"
#include "../Util/Display.h"
#include "../D_Settings.h"

void Water_Renderer :: addChunk ( const Chunk& chunk )
{
    m_chunks.push_back( &chunk );
}

void Water_Renderer :: render( const Camera& camera )
{
    m_shader.useProgram();
    m_shader.loadCameraMatrix(camera);

    m_shader.loadSkyColour  ({Settings::SKY_RED,
                              Settings::SKY_GREEN,
                              Settings::SKY_BLUE
                            });

    glDisable(GL_CULL_FACE);

    for (const Chunk* chunk : m_chunks)
    {
        prepareWater(*chunk);
        glDrawArrays(GL_TRIANGLES, 0, chunk->getMesh().getWaterPart().model.getVertexCount());
    }

    m_chunks.clear      ();
    glBindVertexArray   (0);
    glUseProgram        (0);
}

void Water_Renderer :: prepareWater ( const Chunk& chunk )
{
    chunk.getMesh().getWaterPart().model.bind();
    m_shader.loadChunkMatrix( Maths::createModelMatrix({chunk.getPosition().x, 0, chunk.getPosition().y},
                                                       {0, 0, 0},
                                                       {1, 1, 1}));

    m_shader.loadTime(m_timer.getElapsedTime().asSeconds());
}
