#include "RSolid.h"

#include <iostream>

#include "../Maths/Matrix_Maths.h"

#include "../Camera.h"

#include "../World/Chunk/CSection.h"

namespace Renderer
{
    void RChunk::draw(const Chunk::Section& section)
    {
        m_chunks.push_back(&section);
    }

    void RChunk::update(const Camera& camera)
    {
        //glDisable   (GL_BLEND);
        //glEnable    (GL_CULL_FACE);

        m_shader.bind();

        m_shader.setProjMatrix(camera.getProjectionMatrix());
        m_shader.setViewMatrix(camera.getViewMatrix());

        for (const auto* section : m_chunks)
        {
            prepare(*section);

            glDrawElements(GL_TRIANGLES,
                           section->getMeshes().solidMesh.getModel().getIndicesCount(),
                           GL_UNSIGNED_INT,
                           nullptr);

        }
        m_chunks.clear();
    }

    void RChunk::prepare(const Chunk::Section& section)
    {
        section.getMeshes().solidMesh.getModel().bind();
    }
}
