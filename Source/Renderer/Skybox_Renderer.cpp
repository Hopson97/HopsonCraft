#include "Skybox_Renderer.h"

#include <vector>
#include <GL/glew.h>
#include <iostream>

#include "../Camera.h"

namespace
{
    constexpr GLfloat SIZE = 15000.0f;
    constexpr GLfloat DIST = 500.0f;

    std::vector<GLfloat> vertexPositions =
    {
         SIZE, -SIZE, -DIST,
         SIZE,  SIZE, -DIST,
        -SIZE,  SIZE, -DIST,
        -SIZE, -SIZE, -DIST,
    };

    std::vector<GLfloat> quadTextureCoords =
    {
        1, 0,
        1, 1,
        0, 1,
        0, 0,
    };

    std::vector<GLuint> indices =
    {
        0, 1, 2,
        2, 3, 0
    };
}


Skybox_Renderer::Skybox_Renderer()
:   m_texture("Sky")
{
    m_model.addData(vertexPositions, quadTextureCoords, indices);
}


void Skybox_Renderer::render(const Camera& camera)
{
    m_shader.useProgram();
    m_model.bind();
    m_texture.bind();

    m_shader.loadCameraMatrix(camera);
    glDrawElements(GL_TRIANGLES, m_model.getIndicesCount(), GL_UNSIGNED_INT, nullptr);
}


