#include "RSolid.h"

#include <iostream>

#include "../Maths/Matrix_Maths.h"

#include "../Camera.h"

#include "../World/Chunk/CSection.h"

namespace Renderer
{
    void RChunk::draw(const Chunk::Section& section)
    {
        if (section.getMeshes().solidMesh.getFaceCount() > 0)
        {
            m_renderInfo.emplace_back(section.getMeshes().solidMesh.getModel().getVAO(),
                                      section.getMeshes().solidMesh.getModel().getIndicesCount());
        }
    }

    void RChunk::update(const Camera& camera)
    {
        glEnable (GL_CULL_FACE);
        glDisable(GL_BLEND);

        m_shader.bind();

        m_shader.setProjMatrix(camera.getProjectionMatrix());
        m_shader.setViewMatrix(camera.getViewMatrix());

        for (const auto& section : m_renderInfo)
        {
            glBindVertexArray(section.vao);

            glDrawElements(GL_TRIANGLES,
                           section.indexCount,
                           GL_UNSIGNED_INT,
                           nullptr);

        }
        m_renderInfo.clear();
    }
}
