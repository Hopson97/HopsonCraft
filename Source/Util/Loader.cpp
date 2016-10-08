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

    GLuint loadTexture ( const std::string& file )
    {
        sf::Image image;

        if ( !image.loadFromFile( "Data/Images/" + file + ".png" ) )
        {
            throw std::runtime_error ( "Could not load texture file for " + file + "!" );
        }

        GLuint textureId;
        glGenTextures   ( 1, &textureId );

        glBindTexture(GL_TEXTURE_2D, textureId);
        glTexImage2D    ( GL_TEXTURE_2D, 0, GL_RGBA, image.getSize().x, image.getSize().y, 0,
                          GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr() );

        glGenerateMipmap( GL_TEXTURE_2D );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        return textureId;
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






/*
    Element_Mesh* loadElementMesh ( const std::vector<GLfloat>& vertexCoords,
                                    const std::vector<GLfloat>& textureCoords,
                                    const std::vector<GLuint>&  indices )
    {
        GLuint vao = createVertexArray();

        GLuint elements         = createElementArray( indices );

        GLuint vertexCoordVbo   = storeDataInAttribList( 0, 3, vertexCoords );
        GLuint textureCoordVbo  = storeDataInAttribList( 1, 2, textureCoords );

        return new Element_Mesh();
    }
*/








/*
        GLuint createElementArray( const std::vector<GLuint>& indices )
        {
            GLuint ebo;
            glGenBuffers ( 1, &ebo );
            glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, ebo );
            glBufferData ( GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof ( indices.at( 0 ) ), indices.data(), GL_STATIC_DRAW );
            return ebo;
        }
*/

