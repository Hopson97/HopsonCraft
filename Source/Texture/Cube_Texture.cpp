#include "Cube_Texture.h"

#include <SFML/Graphics/Image.hpp>

Cube_Texture::Cube_Texture(const std::vector<std::string>fileNames)
{
    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_id);

    for (uint32_t i = 0 ; i < fileNames.size() ; i++)
    {
        sf::Image image;
        image.loadFromFile(fileNames[i]);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                     0,
                     GL_RGBA,
                     image.getSize().x,
                     image.getSize().y,
                     0,
                     GL_RGBA,
                     GL_UNSIGNED_BYTE,
                     image.getPixelsPtr());
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Cube_Texture::~Cube_Texture()
{
    glDeleteTextures(1, &m_id);
}


void Cube_Texture::bind()
{
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_id);
}

void Cube_Texture::unbind()
{
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}
