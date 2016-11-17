#include "Solid_Block_Renderer.h"

#include <iostream>

#include "../World/Chunk/Chunk.h"
#include "../Player/Camera.h"
#include "../Maths/Matrix_Maths.h"

#include "Solid_Block_Shader.h"


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
    getShader().loadChunkMatrix( Maths::createModelMatrix({chunk.getPosition().x, 0, chunk.getPosition().y},
                                                          {0, 0, 0},
                                                          {1, 1, 1}));
}

void Solid_Block_Renderer::drawChunk(const Chunk& chunk)
{
    glDrawArrays(GL_TRIANGLES, 0, chunk.getMesh().getSolidPart().model.getVertexCount());
}

