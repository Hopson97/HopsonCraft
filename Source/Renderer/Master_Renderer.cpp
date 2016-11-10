#include "Master_Renderer.h"

void Master_Renderer::processChunk(const Chunk& chunk)
{
    m_chunkRenderer.addChunk    (chunk);
    m_waterRenderer.addChunk    (chunk);
    m_floraRender.addChunk      (chunk);
}

void Master_Renderer::render (const Camera& camera)
{
    m_chunkRenderer.render  (camera);
    m_waterRenderer.render  (camera);
    m_floraRender.render    (camera);
}
