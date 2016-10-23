#include "Texture.h"

#include <SFML/Graphics/Image.hpp>

#include <stdexcept>
#include <iostream>

Texture::Texture(const std::string& textureFileName)
{
    create(textureFileName);
}

Texture::~Texture    ()
{
    glDeleteTextures(1, &m_textureId);
    m_textureId = 0;
}

void Texture::create(const std::string& textureFileName)
{
    glDeleteTextures(1, &m_textureId);

    sf::Image image;
    if (!image.loadFromFile ("Data/Textures/" + textureFileName + ".png")) {
        std::runtime_error ("Could not load file: " + textureFileName);
    }

    glGenTextures(1, &m_textureId);
    glBindTexture(GL_TEXTURE_2D, m_textureId);
    glActiveTexture(GL_TEXTURE0);

    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGBA,
                 image.getSize().x,
                 image.getSize().y,
                 0,
                 GL_RGBA,
                 GL_UNSIGNED_BYTE,
                 image.getPixelsPtr());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

void Texture::bind() const
{
    glBindTexture(GL_TEXTURE_2D, m_textureId);
}

Texture_Atlas::Texture_Atlas(const std::string& textureFileName, size_t imageSize, size_t textureSize)
:   m_texture       (textureFileName)
,   m_imageSize     (imageSize)
,   m_textureSize   (textureSize)
{ }

//Get the UV coords of a single texture from within the texture atlas
std::vector<GLfloat> Texture_Atlas::getTextureCoords(const Vector2& location) const
{
    static size_t texturesPerRow  = m_imageSize / m_textureSize;
    static float  unitSize        = 1.0f / (float)texturesPerRow; //The size of a single texture in normalised GL coord system
    static float  pixelSize       = 1.0f / m_imageSize;

    //Get the coords of the texture in the image in terms of GL UV coords where the bottom left
    //of an image is (0, 0) and the top right is (1, 1).
    float xMin = location.x * unitSize + pixelSize;
    float xMax = xMin       + unitSize - pixelSize;

    float yMin = location.y * unitSize + pixelSize;
    float yMax = yMin       + unitSize - pixelSize;

    return
    {
        xMax, yMax,
        xMin, yMax,
        xMin, yMin,

        xMin, yMin,
        xMax, yMin,
        xMax, yMax
    };
}

void Texture_Atlas::bind() const
{
    m_texture.bind();
}









