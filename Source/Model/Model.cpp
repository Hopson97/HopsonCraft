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

void Model :: bind   () const
{
    glBindVertexArray ( m_glData.vao );
}

void Model :: unbind () const
{
    glBindVertexArray ( 0 );
}


GLuint Model :: getVertexCount() const
{
    return m_glData.vertexCount;
}

Model :: ~Model  ()
{
    deleteData ();
}

void Model :: deleteData ()
{
    glDeleteVertexArrays ( 1, &m_glData.vao );

    glDeleteBuffers ( 1, &m_glData.vertexPosId );
    glDeleteBuffers ( 1, &m_glData.uvCoordsId );
}
