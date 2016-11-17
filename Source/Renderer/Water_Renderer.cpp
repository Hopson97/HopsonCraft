#include "Water_Renderer.h"

#include "../World/Chunk/Chunk.h"
#include "../Maths/Matrix_Maths.h"
#include "../Shaders/Water_Shader.h"


Water_Renderer::Water_Renderer()
{}

void Water_Renderer::prepareRender()
{
    glDisable(GL_CULL_FACE);
}

void Water_Renderer::prepareChunk(const Chunk& chunk)
{
    chunk.getMesh().getWaterPart().model.bind();
    getShader().loadChunkMatrix( Maths::createModelMatrix({chunk.getPosition().x, 0, chunk.getPosition().y},
                                                       {0, 0, 0},
                                                       {1, 1, 1}));

    getShader().loadTime(m_timer.getElapsedTime().asSeconds());
}

void Water_Renderer::drawChunk(const Chunk& chunk)
{
    glDrawArrays(GL_TRIANGLES, 0, chunk.getMesh().getWaterPart().model.getVertexCount());
}
