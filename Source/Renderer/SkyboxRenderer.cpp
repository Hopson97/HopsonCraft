#include "SkyboxRenderer.h"

#include "../Camera.h"
#include "../Texture/CubeTexture.h"

#include "../ModelCoords.h"

#include "../Maths/Matrix.h"

#include <iostream>

namespace Renderer
{
    SkyBox::SkyBox()
    :   m_shader("SkyBox", "SkyBox")
    ,   m_cube  (getCubeVerticies(10.0f, 10.0f), getCubeIndices())
    { }

    void SkyBox::draw(const Texture::CubeTexture& cubeTex)
    {
        m_pCubeMap = &cubeTex;
    }

    void SkyBox::update(const Camera& camera)
    {
        if(!m_pCubeMap) return;

        glDepthMask(GL_FALSE);
        m_shader    .bind();    //shader
        m_cube      .bind();    //VAO
        m_pCubeMap  ->bind();   //texture


        const auto& view = camera.getViewMatrix();
        const auto& proj = camera.getProjMatrix();

        glm::mat4 sView;
        sView = Matrix4(glm::mat3(view));

        m_shader.setProjViewMatrix  (proj * sView);


        glDisable(GL_CULL_FACE);
        glDrawElements(GL_TRIANGLES, m_cube.getIndicesCount(), GL_UNSIGNED_INT, nullptr);

        glDepthMask(GL_TRUE);
        m_pCubeMap = nullptr;
    }
}
