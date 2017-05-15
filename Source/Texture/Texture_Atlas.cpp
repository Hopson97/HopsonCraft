#include "Texture_Atlas.h"

namespace Texture
{
    Atlas::Atlas(const std::string& textureName, GLuint size, GLuint textureSize)
    :   m_size          (size)
    ,   m_textureSize   (textureSize)
    {
        Basic_Texture::loadFromFile(textureName);
    }

    bool Atlas::loadFromFile(const std::string& textureName,
                             GLuint size,
                             GLuint textureSize)
    {
        m_size = size;
        m_textureSize = textureSize;

        return Basic_Texture::loadFromFile(textureName);
    }


    std::vector<GLfloat> Atlas::getTextureCoords(const Vector2& location) const
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
}
