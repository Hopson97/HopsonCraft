#include "Loader.h"

#include <SFML/Graphics/Image.hpp>

#include <stdexcept>



namespace Loader
{
    namespace
    {
        GLuint createVertexArray    ();
        //GLuint createElementArray   ( const std::vector<GLuint>& indices );

        GLuint storeDataInAttribList ( GLuint location, GLuint vertexSize, const std::vector<GLfloat>& data );
    }//Anon Namespace

    Model_Data loadArrayMesh ( const std::vector<GLfloat>& vertexCoords,
                               const std::vector<GLfloat>& textureCoords )
    {
        GLuint vao = createVertexArray();

        GLuint vertexCoordVbo   = storeDataInAttribList( 0, 3, vertexCoords );
        GLuint textureCoordVbo  = storeDataInAttribList( 1, 2, textureCoords );

        return { vao, vertexCoordVbo, textureCoordVbo, vertexCoords.size() / 3 };
    }

    namespace
    {
        GLuint createVertexArray()
        {
            GLuint vao;
            glGenVertexArrays( 1, &vao );
            glBindVertexArray ( vao );
            return vao;
        }

        GLuint storeDataInAttribList ( GLuint location, GLuint vertexSize, const std::vector<GLfloat>& data )
        {
            GLuint vbo;
            glGenBuffers ( 1, &vbo );
            glBindBuffer ( GL_ARRAY_BUFFER, vbo );

            glBufferData ( GL_ARRAY_BUFFER, data.size() * sizeof ( data.at( 0 ) ), data.data(), GL_STATIC_DRAW );

            glVertexAttribPointer       ( location, vertexSize, GL_FLOAT, GL_FALSE, 0, (GLvoid*) 0 );
            glEnableVertexAttribArray   ( location );

            return vbo;
        }
    } //Anon Namespace
}//Loader Namespace
