#include "Model.h"

#include <iostream>

Model_Data :: Model_Data (   GLuint vao,
                             GLuint vertexPosId,
                             GLuint uvCoordsId,
                             size_t vertexCount )
:   vao         ( vao         )
,   vertexPosId ( vertexPosId )
,   uvCoordsId  ( uvCoordsId  )
,   vertexCount ( vertexCount )
{ }

Model :: Model( const Model_Data& data )
:   m_glData    ( data )
{ }

void Model :: addData ( const Model_Data& data )
{
    deleteData ();
    m_glData = data;
}

GLuint Model :: getVAO() const
{
    return m_glData.vao;
}

GLuint Model :: getVertexCount() const
{
    return m_glData.vertexCount;
}

Model :: ~Model  ()
{
    //std::cout << "Deleting Model" << std::endl;
    deleteData ();
}

void Model :: deleteData ()
{
    glDeleteVertexArrays ( 1, &m_glData.vao );

    glDeleteBuffers ( 1, &m_glData.vertexPosId );
    glDeleteBuffers ( 1, &m_glData.uvCoordsId );
}
