#include "Model.h"

#include <stdexcept>
#include <iostream>

Model::Model (const std::vector<GLfloat>& vertexCoords, const std::vector<GLfloat>& textureCoords)
{
    create(vertexCoords, textureCoords);
}

Model::~Model()
{
    deleteObjects();
}

void Model::create(const std::vector<GLfloat>& vertexCoords, const std::vector<GLfloat>& textureCoords)
{
    //deleteObjects();
    std::cout << "Creating model..." << std::endl;
    glGenVertexArrays   (1, &m_vao);
    glBindVertexArray   (m_vao);

    createVBO (m_vertexCoords,  0, 3, vertexCoords);
    createVBO (m_textureCoords, 1, 2, textureCoords);

    m_vertexCount = vertexCoords.size() / 3;
    glBindVertexArray(0);

}

void Model::createVBO (GLuint& vbo, GLuint location, GLuint vertexSize, const std::vector<GLfloat>& data )
{
    glGenBuffers (1, &vbo);
    glBindBuffer (GL_ARRAY_BUFFER, vbo);
    glBufferData (GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), data.data(), GL_STATIC_DRAW);

    glVertexAttribPointer (location, vertexSize, GL_FLOAT, GL_FALSE, 0, (GLvoid*) 0);
    glEnableVertexAttribArray (location);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Model::deleteObjects()
{
    std::cout << "Deleting model!" << std::endl;
    glDeleteBuffers     (1, &m_vertexCoords);
    glDeleteBuffers     (1, &m_textureCoords);
    glDeleteVertexArrays(1, &m_vao);

    m_vertexCoords = 0;
    m_textureCoords = 0;
    m_vao = 0;
}

void Model::bind() const
{
    glBindVertexArray(m_vao);
}

GLuint Model::getVertexCount() const
{
    return m_vertexCount;
}


