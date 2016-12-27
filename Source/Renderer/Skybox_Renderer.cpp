#include "Skybox_Renderer.h"

#include <vector>
#include <GL/glew.h>
#include <iostream>

#include "../Camera.h"

namespace
{
    constexpr GLfloat SIZE = 5.0f;

    std::vector<GLfloat> vertexPositions =
    {
        //Back
        SIZE, -SIZE, -SIZE,
        -SIZE, -SIZE, -SIZE,
        -SIZE, SIZE, -SIZE,
        SIZE, SIZE, -SIZE,

        //Right-Side
        SIZE, -SIZE, SIZE,
        SIZE, -SIZE, -SIZE,
        SIZE, SIZE, -SIZE,
        SIZE, SIZE, SIZE,

        //Front
        -SIZE, -SIZE, SIZE,
        SIZE, -SIZE, SIZE,
        SIZE, SIZE, SIZE,
        -SIZE, SIZE, SIZE,

        //Left
        -SIZE, -SIZE, -SIZE,
        -SIZE, -SIZE, SIZE,
        -SIZE, SIZE, SIZE,
        -SIZE, SIZE, -SIZE,

        //Top
        -SIZE, SIZE, SIZE,
        SIZE, SIZE, SIZE,
        SIZE, SIZE, -SIZE,
        -SIZE, SIZE, -SIZE,

        //Bottom
        -SIZE, -SIZE, -SIZE,
        SIZE, -SIZE, -SIZE,
        SIZE, -SIZE, SIZE,
        -SIZE, -SIZE, SIZE
    };

    std::vector<GLuint> indices =
    {
        0, 1, 2,
        2, 3, 0,

        4, 5, 6,
        6, 7, 4,

        8, 9, 10,
        10, 1, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };
}

std::vector<std::string> files =
{
    "Data/Images/Skybox/right.png",
    "Data/Images/Skybox/left.png",
    "Data/Images/Skybox/top.png",
    "Data/Images/Skybox/bottom.png",
    "Data/Images/Skybox/back.png",
    "Data/Images/Skybox/front.png"
};

Skybox_Renderer::Skybox_Renderer()
:   m_texture(files)
{
    m_model.addData(vertexPositions, {}, indices);
}


void Skybox_Renderer::render(const Camera& camera)
{
    m_shader.useProgram();
    m_model.bind();
    m_texture.bind();

    m_shader.loadCameraMatrix(camera);
    glDrawElements(GL_TRIANGLES, m_model.getIndicesCount(), GL_UNSIGNED_INT, nullptr);
}


