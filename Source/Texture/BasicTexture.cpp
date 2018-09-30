#include "BasicTexture.h"

#include <SFML/Graphics/Image.hpp>

bool BasicTexture::loadFromFile(const std::string& fileName)
{
    clear();
    std::string filePath = "Data/Textures/" + fileName + ".png";

    sf::Image image;
    if (!image.loadFromFile(filePath))
    {
        return false;
    }

    glGenTextures(1, &m_textureID);
    glBindTexture(GL_TEXTURE_2D, m_textureID);

    //glGenerateMipmap(GL_TEXTURE_2D);
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGBA,
                 image.getSize().x,
                 image.getSize().y,
                 0,
                 GL_RGBA,
                 GL_UNSIGNED_BYTE,
                 image.getPixelsPtr());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    return true;
}

BasicTexture::~BasicTexture()
{
    clear();
}

    void BasicTexture::clear()
    {
        glDeleteTextures(1, &m_textureID);
    }


    void BasicTexture::bind() const
    {
        glBindTexture(GL_TEXTURE_2D, m_textureID);
    }

    void BasicTexture::unbind() const
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
