#include "Texture_Atlas.h"

#include <unordered_map>

namespace
{
    //There is only one block atlas, so I can do this to work around the "getTextureCoords" being a const function
    std::unordered_map<Vector2, std::vector<GLfloat>> textureLocationCache;
}

Texture_Atlas::Texture_Atlas (float imageSize, float textureSize, const std::string& file)
:   Texture         (file)
,   m_size          (imageSize)
,   m_textureSize   (textureSize)
{

}

std::vector<GLfloat>& Texture_Atlas::getTextureCoords (const Vector2& location) const
{
    if (textureLocationCache.find(location) == textureLocationCache.end())
    {
        static float txrPerRow = m_size / m_textureSize;
        static float unitSize  = 1.0f   / txrPerRow;

        float xMin  = location.x * unitSize;
        float yMin  = location.y * unitSize;
        float xMax  = xMin + unitSize;
        float yMax  = yMin + unitSize;

        textureLocationCache.insert(std::make_pair(
        location,
        std::vector<GLfloat>
        {
            xMax, yMax,
            xMin, yMax,
            xMin, yMin,
            xMax, yMin,
        }));
    }

    return textureLocationCache[location];
}
