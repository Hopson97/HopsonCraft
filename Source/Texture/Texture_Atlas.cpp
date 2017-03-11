#include "Texture_Atlas.h"

namespace Texture
{
    Atlas::Atlas(const std::string& textureName, GLuint size, GLuint textureSize)
    :   m_size          (size)
    ,   m_textureSize   (textureSize)
    {
        load(textureName);
    }
/*
    std::vector<GLfloat> Atlas::getTextureCoords(const Vector2& location) const
    {
        static auto texturesPerRow  = m_size / m_textureSize;
        static auto unitSize        = 1.0f / (float)texturesPerRow;

        auto xMin = location.x * unitSize;
        auto yMin = location.y * unitSize;

        auto xMax = xMin + unitSize;
        auto yMax = yMin + unitSize;

        return
        {
            xMax, yMax,
            xMin, yMax,
            xMin, yMin,
            xMax, yMin
        };
    }
    */

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
