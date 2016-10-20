#include "Master_Renderer.h"

void Master_Renderer :: processChunk( const Chunk& chunk )
{
    m_chunkRenderer.addChunk ( chunk );
    m_waterRenderer.addChunk ( chunk );
}

void Master_Renderer :: render ( const Camera& camera, const Vector2i& playerLocation )
{
    m_chunkRenderer.render ( camera, playerLocation );
    m_waterRenderer.render ( camera );
}
