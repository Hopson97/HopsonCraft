#include "Texture.h"


#include <SFML/Graphics/Image.hpp>
#include <stdexcept>
#include "../Util/Display.h"

Texture::Texture (const std::string& file)
{
    loadFromFile(file);
}

void Texture::loadFromFile (const std::string& file)
{
    sf::Image image;

    if ( !image.loadFromFile( "Data/Images/" + file + ".png" ) )
    {
        throw std::runtime_error ( "Could not load texture file for " + file + "!" );
    }

    create(image.getSize().x, image.getSize().y, image.getPixelsPtr());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    auto aniso = 4.0f;
    glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &aniso);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, aniso);
}

void Texture::createEmpty(int width, int height)
{
    create(width, height, nullptr);
}

void Texture::create(int width, int height, const void* data)
{
    glGenTextures   ( 1, &m_textureID );

    glBindTexture(GL_TEXTURE_2D, m_textureID);
    glTexImage2D    ( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
                      GL_RGBA, GL_UNSIGNED_BYTE, data );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}


void Texture::bind   ()
{
    glBindTexture(GL_TEXTURE_2D, m_textureID);
}

void Texture::unbind ()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}


//This returns a reference so it does not get glDeleted
const GLuint& Texture::getID() const
{
    return m_textureID;
}


Texture::~Texture()
{
    glDeleteTextures(1, &m_textureID);
}
