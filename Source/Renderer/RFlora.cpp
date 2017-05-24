#include "RFlora.h"

#include <iostream>

#include "../Maths/Matrix_Maths.h"

#include "../Camera.h"

#include "../World/Chunk/Section.h"

namespace Renderer
{
    RFlora::RFlora()
    :   m_shader("Flora")
    {

    }

    void RFlora::draw(const Chunk::Section& section)
    {
        if (section.getMeshes().floraMesh.getFaceCount() > 0)
        {
            m_renderInfo.emplace_back(section.getMeshes().floraMesh.getModel().getVAO(),
                                      section.getMeshes().floraMesh.getModel().getIndicesCount());
        }
    }

    void RFlora::update(const Camera& camera)
    {
        glDisable (GL_CULL_FACE);

        m_shader.bind();

        m_shader.setProjViewMatrix(camera.getProjectionViewMatrix());
        m_shader.loadTimer(m_windTimer.getElapsedTime().asSeconds());

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
