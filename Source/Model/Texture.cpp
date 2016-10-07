#include "Texture.h"

#include "Loader.h"

#include <iostream>

Texture :: Texture ( int textureID )
:   m_textureID ( textureID )
{

}

void Texture :: loadFromFile ( const std::string& file )
{
    m_textureID = Loader::loadTexture ( file );
}

GLuint Texture :: getId () const
{
    return m_textureID;
}


Texture :: ~Texture()
{
    std::cout << "Deleting Texture " << m_textureID << "\n";
    //glDeleteTextures( 1, &m_textureID );
}
