#include "RSkyBox.h"

#include "../Camera.h"
#include "../Texture/CubeTexture.h"

#include "../ModelCoords.h"

#include "../Maths/Matrix.h"

#include <iostream>

float skyboxVertices[] = {
    // positions
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f
};

GLuint vbo;

namespace Renderer
{
    SkyBox::SkyBox()
    :   m_shader("SkyBox", "SkyBox")
    //,   m_cube  (getCubeVerticies(10.0f, 10.0f), getCubeIndices())
    {
        glBindVertexArray(0);

            glGenBuffers(1, &vbo);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER,
                     sizeof(skyboxVertices),
                     skyboxVertices,
                     GL_STATIC_DRAW);

        glVertexAttribPointer(0,
                              3,
                              GL_FLOAT,
                              GL_FALSE,
                              0,
                              (GLvoid*) 0);

    }

    void SkyBox::draw(const Texture::CubeTexture& cubeTex)
    {
        m_pCubeMap = &cubeTex;
    }

    void SkyBox::update(const Camera& camera)
    {
        if(!m_pCubeMap) return;

        glDepthMask(GL_FALSE);
        m_shader    .bind();    //shader
        //m_cube      .bind();    //VAO
        m_pCubeMap  ->bind();   //texture

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        const auto& view = camera.getViewMatrix();
        const auto& proj = camera.getProjMatrix();

        auto sView = Matrix4(glm::mat3(view));

        m_shader.setProjViewMatrix  (proj * sView);

        glDrawArrays(GL_TRIANGLES, 0, 36);

        //glDisable(GL_CULL_FACE);
        //glDrawElements(GL_TRIANGLES, m_cube.getIndicesCount(), GL_UNSIGNED_INT, nullptr);

        glDepthMask(GL_TRUE);
        m_pCubeMap = nullptr;
    }
}
