#include "TextureAtlas.h"

TextureAtlas::TextureAtlas(const std::string& textureName, GLuint size, GLuint textureSize)
:   m_size          (size)
,   m_textureSize   (textureSize)
{
    BasicTexture::loadFromFile(textureName);
}

bool TextureAtlas::loadFromFile(const std::string& textureName,
                         GLuint size,
                         GLuint textureSize)
{
    m_size = size;
    m_textureSize = textureSize;

    return BasicTexture::loadFromFile(textureName);
}


std::vector<GLfloat> TextureAtlas::getTextureCoords(const Vector2& location) const
{
    static float texturesPerRow     = m_size / m_textureSize;
    static float unitSize           = 1.0f / (float)texturesPerRow;
    static float pixelSize          = 1.0f / (float)m_size;

    float xMin = (location.x * unitSize) + 0.5 * pixelSize;
    float yMin = (location.y * unitSize) + 0.5 * pixelSize;

    float xMax = (xMin + unitSize) - 0.5 * pixelSize;
    float yMax = (yMin + unitSize) - 0.5 * pixelSize;

    return
    {
        xMax, yMax,
        xMin, yMax,
        xMin, yMin,
        xMax, yMin
    };
}

