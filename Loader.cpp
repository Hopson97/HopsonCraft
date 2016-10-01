#include "Loader.h"

#include <SFML/Graphics/Image.hpp>

Loader :: ~Loader ()
{
    for(auto& i : this->vaoList)
        glDeleteVertexArrays(1, &i);

    for(auto& i : this->vboList)
        glDeleteBuffers(1, &i);

    for(auto& i : this->textureList)
        glDeleteTextures(1, &i);
}


//The meshes have to be pointers, or else if I return a copy, the destructor is called on the local copy and thus OpenGL
//deletes the vertex arrays (from the destructor)
MeshPtr Loader :: loadToVAO( const std::vector<GLfloat>&  positions,
                            const std::vector<GLuint>&   indices,
                            const std::vector<GLfloat>&  texture )
{
    GLuint id = createVAO();
    bindIndexBuffer ( indices );

    GLuint vert = storeDataInAttributeList( 0, 3, positions );
    GLuint txr = storeDataInAttributeList( 1, 2, texture );
    unbindVAO();

    return std::make_unique<Mesh>( id, indices.size(), vert, txr );
}

MeshPtr Loader :: loadToVAO(   const std::vector<GLfloat>&  positions,
                            const std::vector<GLfloat>&  texture )
{
    GLuint id = createVAO();

    GLuint vert = storeDataInAttributeList( 0, 3, positions );
    GLuint txr = storeDataInAttributeList( 1, 2, texture );
    unbindVAO();

    return std::make_unique<Mesh>( id, positions.size() / 3, vert, txr );
}

GLuint Loader :: loadTexture ( const std::string& fileName )
{
    sf::Image image;
    image.loadFromFile( "Data/Images/" + fileName + ".png" );

    GLuint textureID;
    glGenTextures( 1, &textureID );
    textureList.push_back( textureID );

    image.flipVertically();

    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getSize().x, image.getSize().y, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());

    glGenerateMipmap( GL_TEXTURE_2D );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    return textureID;
}



void Loader :: bindIndexBuffer( const std::vector<GLuint>& indices )
{
    createVBO( GL_ELEMENT_ARRAY_BUFFER );
    glBufferData ( GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof ( indices.at( 0 ) ), indices.data(), GL_STATIC_DRAW );
}


//Vertex ARRAY object
GLuint Loader::createVAO()
{
    GLuint id;
    glGenVertexArrays( 1, &id );
    glBindVertexArray ( id );

    vaoList.push_back( id );
    return id;
}

//Vertex BUFFER object
GLuint Loader::createVBO( GLenum type )
{
    GLuint vbo;
    glGenBuffers( 1, &vbo );
    glBindBuffer ( type, vbo );

    vboList.push_back (  vbo );
    return vbo;
}


void Loader :: unbindVAO()
{
    glBindVertexArray ( 0 );
}
