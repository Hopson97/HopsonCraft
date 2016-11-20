#include "Flora_Renderer.h"

#include "../World/Chunk/Chunk.h"
#include "../Maths/Matrix_Maths.h"
#include "../Shaders/Flora_Shader.h"

Flora_Renderer::Flora_Renderer()
{ }

void Flora_Renderer::prepareRender()
{
    glDisable(GL_CULL_FACE);
}

void Flora_Renderer::prepareChunk (const Chunk& chunk)
{
    chunk.getMesh().getFloraPart().model.bind();
    getShader().loadChunkMatrix(chunk.getModelMatrix());
    getShader().loadTime(m_timer.getElapsedTime().asSeconds());
}

void Flora_Renderer::drawChunk(const Chunk& chunk)
{
    glDrawElements(GL_TRIANGLES,
                   chunk.getMesh().getSolidPart().model.getVertexCount(),
                   GL_UNSIGNED_INT,
                   nullptr);
}
