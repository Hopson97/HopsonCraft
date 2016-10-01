#include "Mesh.h"

#include <iostream>

Mesh :: Mesh( GLuint vao, GLuint count, GLuint vert, GLuint txr )
:   m_vao   ( vao   )
,   m_count ( count )
,   m_vert  ( vert  )
,   m_txr   ( txr   )
{ }

GLuint Mesh::getVAO() const
{
    return m_vao;
}

GLuint Mesh::getVertexCount() const
{
    return m_count;
}


Mesh :: ~Mesh()
{
    glDeleteBuffers     ( 1, &m_vert );
    glDeleteBuffers     ( 1, &m_txr );
    glDeleteVertexArrays( 1, &m_vao );
}
