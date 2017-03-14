#include "RChunk.h"

#include <iostream>

#include "../World/Chunk/CColumn.h"
#include "../Maths/Matrix_Maths.h"

#include "../Camera.h"

namespace Renderer
{
    void RChunk::draw(const Chunklet& chunklet)
    {
        m_chunks.push_back(&chunklet);
    }

    void RChunk::update(const Camera& camera)
    {
        glDisable   (GL_BLEND);
        glEnable    (GL_CULL_FACE);

        m_shader.bind();

        m_shader.setProjMatrix(camera.getProjectionMatrix());
        m_shader.setViewMatrix(camera.getViewMatrix());

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
