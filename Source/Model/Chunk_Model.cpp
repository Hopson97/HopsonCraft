#include "Chunk_Model.h"

namespace
{
    GLuint createVertexArray()
    {
        GLuint vao;
        glGenVertexArrays(1, &vao);
        glBindVertexArray (vao);
        return vao;
    }

    GLuint storeDataInAttribList (GLuint location, GLuint vertexSize, const std::vector<GLfloat>& data)
    {
        GLuint vbo;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo );

        glBufferData(GL_ARRAY_BUFFER,
                     data.size() * sizeof (data.at(0)),
                     data.data(),
                     GL_STATIC_DRAW);

        glVertexAttribPointer(location,
                              vertexSize,
                              GL_FLOAT,
                              GL_FALSE,
                              0,
                              (GLvoid*) 0);

        glEnableVertexAttribArray (location);
        return vbo;
    }

    Chunk_Model_Data load (const std::vector<GLfloat>& vertexCoords,
                           const std::vector<GLfloat>& textureCoords,
                           const std::vector<GLfloat>& lightValues,
                           const std::vector<GLuint>& indices)
    {
        GLuint vao = createVertexArray();

        GLuint vertexCoordVbo   = storeDataInAttribList(0, 3, vertexCoords);
        GLuint textureCoordVbo  = storeDataInAttribList(1, 2, textureCoords);
        GLuint lightCoordVbo    = storeDataInAttribList(2, 1, lightValues);

        GLuint eboVbo;
        glGenBuffers(1, &eboVbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboVbo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                     indices.size() * sizeof (indices.at(0)),
                     indices.data(),
                     GL_STATIC_DRAW);

        glBindVertexArray(0);

        return {vao, vertexCoordVbo, textureCoordVbo, lightCoordVbo, eboVbo, indices.size()};
    }
} //Anon Namespace

//Model Data
Chunk_Model_Data::Chunk_Model_Data (    GLuint vao,
                    GLuint vertexPosId,
                    GLuint uvCoordsId,
                    GLuint lightId,
                    GLuint eboId,
                    size_t indicesCount )
:   vao         (vao )
,   vertexPosId (vertexPosId)
,   uvCoordsId  (uvCoordsId)
,   lightID     (lightId)
,   eboId       (eboId)
,   indicesCount (indicesCount)
{ }

void Chunk_Model::addData(const std::vector<GLfloat>& vertexCoords, const std::vector<GLfloat>& textureCoords, const std::vector<GLfloat>& colour, const std::vector<GLuint>& indices)
{
    deleteData ();
    m_glData = load(vertexCoords, textureCoords, colour, indices);
}

void Chunk_Model::bind() const
{
    glBindVertexArray (m_glData.vao);
}

void Chunk_Model::unbind() const
{
    glBindVertexArray (0);
}

GLuint Chunk_Model::getVertexCount() const
{
    return m_glData.indicesCount;
}

Chunk_Model::~Chunk_Model()
{
    deleteData();
}

void Chunk_Model::deleteData()
{
    glDeleteVertexArrays (1, &m_glData.vao);

    glDeleteBuffers (1, &m_glData.vertexPosId);
    glDeleteBuffers (1, &m_glData.uvCoordsId);
    glDeleteBuffers (1, &m_glData.eboId);
    glDeleteBuffers (1, &m_glData.lightID);
}
