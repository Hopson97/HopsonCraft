#include "Texture.h"

#include "../Loader.h"

#include <iostream>

Texture :: Texture ( const std::string& file )
:   m_textureID ( Loader::loadTexture ( file ) )
{ }

void Texture :: loadFromFile ( const std::string& file )
{
    m_textureID = Loader::loadTexture ( file );
}

void Texture :: bind   ()
{
    glBindTexture( GL_TEXTURE_2D, m_textureID );
}

void Texture :: unbind ()
{
    glBindTexture( GL_TEXTURE_2D, 0 );
}

Texture :: ~Texture()
{
    glDeleteTextures( 1, &m_textureID );
}
