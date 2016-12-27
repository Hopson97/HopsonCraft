#include "Skybox_Renderer.h"

#include <vector>
#include <GL/glew.h>
#include <iostream>

#include "../Camera.h"

namespace
{
    constexpr GLfloat SIZE = 450.0f;

    std::vector<GLfloat> vertexPositions =
    {
        //Bottom
        -SIZE,  SIZE  -SIZE,
        -SIZE, -SIZE  -SIZE,
         SIZE, -SIZE  -SIZE,
         SIZE,  SIZE, -SIZE

         //Back
        -SIZE, -SIZE,  SIZE,
        -SIZE, -SIZE, -SIZE,
        -SIZE,  SIZE, -SIZE,
        -SIZE,  SIZE,  SIZE,

        //
        SIZE, -SIZE, -SIZE,
        SIZE, -SIZE,  SIZE,
        SIZE,  SIZE,  SIZE,
        SIZE,  SIZE, -SIZE,

        //
        -SIZE, -SIZE, SIZE,
        -SIZE,  SIZE, SIZE,
         SIZE,  SIZE, SIZE,
         SIZE, -SIZE, SIZE,

        //
        -SIZE, SIZE, -SIZE,
         SIZE, SIZE, -SIZE,
         SIZE, SIZE,  SIZE,
        -SIZE, SIZE,  SIZE,

        -SIZE, -SIZE, -SIZE,
        -SIZE, -SIZE,  SIZE,
         SIZE, -SIZE, -SIZE,
        -SIZE, -SIZE,  SIZE,
    };

    std::vector<GLuint> indices =
    {
        0, 1, 2,
        2, 3, 0,


    };

    std::vector<GLuint> getIndices()
    {
        std::vector<GLuint> indices(6 * 6);
        for (GLuint i = 0 ; i < 4 * 6 ; i += 4)
        {
            indices.insert(indices.end(),
            {
                0 + i, 1 + i, 2 + i,
                2 + i, 3 + i, 0 + i
            });
        }
        return indices;
    }
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
    m_model.addData(vertexPositions, {}, getIndices());
}


void Skybox_Renderer::render(const Camera& camera)
{
    std::cout << "Drawing" << std::endl;
    m_shader.useProgram();
    m_model.bind();
    m_texture.bind();

    m_shader.loadCameraMatrix(camera);
    glDrawElements(GL_TRIANGLES, m_model.getIndicesCount(), GL_UNSIGNED_INT, nullptr);
}


