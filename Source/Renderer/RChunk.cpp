#include "RChunk.h"

#include <iostream>

#include "../World/Chunk/Terrain/CColumn.h"
#include "../Maths/Matrix_Maths.h"

namespace Renderer
{
    void RChunk::draw(const Chunklet& chunklet)
    {
        m_chunks.push_back(&chunklet);
    }

    void RChunk::update(const Matrix4& viewMatrix)
    {
        glDisable   (GL_BLEND);
        glEnable    (GL_CULL_FACE);

        m_shader.bind();

        m_shader.setViewMatrix(viewMatrix);

        for (const Chunklet* chunklet : m_chunks)
        {
            prepare(*chunklet);
            glDrawElements(GL_TRIANGLES,
                           chunklet->getMesh().getSolidMesh().getModel().getIndicesCount(),
                           GL_UNSIGNED_INT,
                           nullptr);
        }
        m_chunks.clear();
    }

    void RChunk::prepare(const Chunklet& chunklet)
    {
        chunklet.getMesh().getSolidMesh().getModel().bind();
        m_shader.setModelMatrix(chunklet.getMat());

    }
}
