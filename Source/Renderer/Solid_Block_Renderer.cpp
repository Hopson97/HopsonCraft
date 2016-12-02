#include "Solid_Block_Renderer.h"

#include "../World/Chunk/Chunk.h"
#include "../Player/Camera.h"
#include "../Maths/Matrix_Maths.h"

#include "../Shaders/Solid_Block_Shader.h"


Solid_Block_Renderer::Solid_Block_Renderer()
{ }

void Solid_Block_Renderer::prepareRender()
{
    glEnable    (GL_CULL_FACE);
    glCullFace  (GL_BACK);
}

void Solid_Block_Renderer::prepareChunk (const Chunk& chunk)
{
    chunk.getMesh().getSolidPart().model.bind();
    getShader().loadChunkMatrix(chunk.getModelMatrix());
}

void Solid_Block_Renderer::drawChunk(const Chunk& chunk)
{
    glDrawElements(GL_TRIANGLES,
                   chunk.getMesh().getSolidPart().model.getIndicesCount(),
                   GL_UNSIGNED_INT,
                   nullptr);
}

