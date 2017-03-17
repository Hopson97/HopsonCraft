
#include "RSimple.h"
#include "../Temp/Quad.h"
#include "../Maths/Matrix_Maths.h"
#include "../Maths/Matrix_Maths.h"

#include "../Camera.h"

namespace Renderer
{
    void RSimple::draw(const Quad& quad)
    {
        m_quads.push_back(&quad);
    }

    void RSimple::update(const Camera& camera)
    {
        m_shader.bind();

        m_shader.setProjMatrix(camera.getProjectionMatrix());
        m_shader.setViewMatrix(camera.getViewMatrix());

        for (auto& quad : m_quads)
        {
            prepare(*quad);
            glDrawElements(GL_TRIANGLES, quad->getModel().getIndicesCount(), GL_UNSIGNED_INT, nullptr);
        }

        m_quads.clear();
    }

    void RSimple::prepare(const Quad& quad)
    {
        quad.getModel().bind();
        m_shader.setModelMatrix(Maths::createModelMatrix(quad));

    }
}

