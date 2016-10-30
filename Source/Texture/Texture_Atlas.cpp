
#include "Texture_Atlas.h"

#include <cmath>
#include <iostream>

Texture_Atlas :: Texture_Atlas (float imageSize, float textureSize, const std::string& file )
:   Texture         ( file )
,   m_size          ( imageSize )
,   m_textureSize   ( textureSize )
{

}

std::vector<GLfloat> Texture_Atlas :: getTextureCoords ( Vector2 location ) const
{
    static float txrPerRow = m_size / m_textureSize;
    static float unitSize  = 1.0f   / txrPerRow;
    //static float pixelSize = (1.0f   / m_size);

    float xMin  = location.x * unitSize;
    float yMin  = location.y * unitSize;
    float xMax  = xMin + unitSize;
    float yMax  = yMin + unitSize;

    return
    {
        xMax, yMax,
        xMin, yMax,
        xMin, yMin,


        xMin, yMin,
        xMax, yMin,
        xMax, yMax,
    };
}
