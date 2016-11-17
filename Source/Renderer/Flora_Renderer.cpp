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
    getShader().loadChunkMatrix( Maths::createModelMatrix( { chunk.getPosition().x, 0, chunk.getPosition().y },
                                                           { 0, 0, 0 },
                                                        { 1, 1, 1 } ) );
}

void Flora_Renderer::drawChunk(const Chunk& chunk)
{
    glDrawArrays(GL_TRIANGLES, 0, chunk.getMesh().getFloraPart().model.getVertexCount());
}
