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
    getShader().loadChunkMatrix(chunk.getModelMatrix());
    getShader().loadTime(m_timer.getElapsedTime().asSeconds());
}

void Water_Renderer::drawChunk(const Chunk& chunk)
{
    glDrawElements(GL_TRIANGLES,
                   chunk.getMesh().getSolidPart().model.getVertexCount(),
                   GL_UNSIGNED_INT,
                   nullptr);
}
