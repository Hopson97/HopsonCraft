#include "Chunk_Ground_Renderer.h"

#include "Chunk.h"
#include "Camera.h"
#include "Maths/Matrix_Maths.h"

Chunk_Ground_Renderer::Chunk_Ground_Renderer()
:   m_shader ("Ground_Vertex", "Ground_Fragment")
{

}


void Chunk_Ground_Renderer::processChunk (const Chunk& chunk)
{
    m_chunks.push_back(&chunk);
}

void Chunk_Ground_Renderer::render (const Camera& camera)
{
    m_shader.useProgram();
    m_shader.loadCameraMatrix(camera);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    for(auto& chunk : m_chunks) {
        prepareChunk(*chunk);
        glDrawArrays(GL_TRIANGLES, 0, chunk->getMesh().getSolidPart().model.getVertexCount());
    }
    m_chunks.clear();
}


void Chunk_Ground_Renderer::prepareChunk (const Chunk& chunk)
{
    chunk.getMesh().getSolidPart().model.bind();
    m_shader.loadChunkMatrix(Maths::createModelMatrix(chunk.getGlPosition(),
                                                      {0, 0, 0},
                                                      {1, 1, 1}));
}
