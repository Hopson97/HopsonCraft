#include "RFlora.h"

#include <iostream>

#include "../Maths/Matrix_Maths.h"

#include "../Camera.h"

#include "../World/Chunk/CSection.h"

namespace Renderer
{
    void RFlora::draw(const Chunk::Section& section)
    {
        m_renderInfo.emplace_back(section.getMeshes().floraMesh.getModel().getVAO(),
                                  section.getMeshes().floraMesh.getModel().getIndicesCount());
    }

    void RFlora::update(const Camera& camera)
    {
        glDisable (GL_CULL_FACE);

        m_shader.bind();

        m_shader.setProjMatrix(camera.getProjectionMatrix());
        m_shader.setViewMatrix(camera.getViewMatrix());
        m_shader.loadWindTimer(m_waveTimer.getElapsedTime().asSeconds());

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
