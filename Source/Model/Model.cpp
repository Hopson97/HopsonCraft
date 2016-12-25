#include "Model.h"

//Model
void Model::addData (const std::vector<GLfloat>& vertexCoords,
                     const std::vector<GLfloat>& textureCoords,
                     const std::vector<GLuint>& indices)
{
    deleteBuffers();   //Delete any buffers that may have been previously stored in this model
    m_vboCount = 0;

    glGenVertexArrays(1, &m_vao);
    bind();

    addVBO(3, vertexCoords);
    addVBO(2, textureCoords);
    addEBO(indices);

    m_indicesCount = indices.size();
}

void Model::bind () const
{
    glBindVertexArray (m_vao);
}

void Model::unbind () const
{
    glBindVertexArray (0);
}

GLuint Model::getIndicesCount() const
{
    return m_indicesCount;
}

Model::~Model  ()
{
    deleteBuffers ();
}

void Model::addVBO (GLuint vertexSize, const std::vector<GLfloat>& data)
{
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo );

    glBufferData(GL_ARRAY_BUFFER,
                 data.size() * sizeof (data[0]),
                 data.data(),
                 GL_STATIC_DRAW);

    glVertexAttribPointer(m_vboCount,
                          vertexSize,
                          GL_FLOAT,
                          GL_FALSE,
                          0,
                          (GLvoid*) 0);

    glEnableVertexAttribArray (m_vboCount);
    m_vboCount++;
    m_buffers.push_back(vbo);
}

void Model::addEBO(const std::vector<GLuint>& indices)
{
        GLuint ebo;
        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                     indices.size() * sizeof (indices.at(0)),
                     indices.data(),
                     GL_STATIC_DRAW);
        m_buffers.push_back(ebo);
}

void Model::deleteBuffers ()
{
    glDeleteVertexArrays (1, &m_vao);
    glDeleteBuffers(m_buffers.size(), m_buffers.data());
}
