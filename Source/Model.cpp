#include "Model.h"

#include <iostream>
#include <stdexcept>

Model::Model(const std::vector<GLfloat>& vertexPositions,
             const std::vector<GLfloat>& textureCoordinates,
             const std::vector<GLuint>&  indices)
:   m_indicesCount  (indices.size())
{
    glGenVertexArrays(1, &m_vao);
    bind();

    addVBO(3, vertexPositions);
    addVBO(2, textureCoordinates);
    addEBO(indices);
}

Model::Model(Model&& other)
:   m_vao           (other.m_vao)
,   m_vboCount      (other.m_vboCount)
,   m_indicesCount  (other.m_indicesCount)
,   m_buffers       (std::move(other.m_buffers))
{
    other.m_vao         = 0;
    other.m_vboCount    = 0;
    other.m_buffers.clear();
}

Model& Model::operator=(Model&& other)
{
    m_vao           = other.m_vao;
    m_vboCount      = other.m_vboCount;
    m_indicesCount  = other.m_indicesCount;
    m_buffers   = std::move(other.m_buffers);

    other.m_vao         = 0;
    other.m_vboCount    = 0;
    other.m_buffers.clear();

    return *this;
}



Model::~Model()
{
    deleteData();
}

void Model::addData(const std::vector<GLfloat>& vertexPositions,
                    const std::vector<GLfloat>& textureCoordinates,
                    const std::vector<GLuint>&  indices)
{
    deleteData();

    m_indicesCount = indices.size();
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    addVBO(3, vertexPositions);
    addVBO(2, textureCoordinates);
    addEBO(indices);
}

void Model::deleteData()
{
    glDeleteBuffers(m_buffers.size(), m_buffers.data());
    glDeleteVertexArrays(1, &m_vao);

    m_vao = 0;
    m_vboCount = 0;
    m_indicesCount = 0;
}


void Model::bind() const
{
    glBindVertexArray(m_vao);
}

void Model::unbind() const
{
    glBindVertexArray(0);
}

GLuint Model::getIndicesCount() const
{
    return m_indicesCount;
}

void Model::addVBO(int dim, const std::vector<GLfloat>& data)
{
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER,
                 data.size() * sizeof(data[0]),
                 data.data(),
                 GL_STATIC_DRAW);

    glVertexAttribPointer(m_vboCount,
                          dim,
                          GL_FLOAT,
                          GL_FALSE,
                          0,
                          (GLvoid*) 0);

    glEnableVertexAttribArray(m_vboCount++);

    m_buffers.push_back(vbo);
}

GLuint Model::getVAO() const
{
    return m_vao;
}



void Model::addEBO(const std::vector<GLuint>& indices)
{
    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 indices.size() * sizeof (indices[0]),
                 indices.data(),
                 GL_STATIC_DRAW);

    m_buffers.push_back(ebo);
}
