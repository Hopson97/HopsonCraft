#ifndef TEXTURE_ATLAS_H
#define TEXTURE_ATLAS_H

#include <vector>

#include "../OpenGL/Glew/glew.h"
#include "../OpenGL/Glm/glm_transformations.h"

#include "Texture.h"

class Texture_Atlas : public Texture
{
    public:
        Texture_Atlas( float imageSize, float textureSize, const std::string& file );

        std::vector<GLfloat> getTextureCoords ( Vector2 location ) const;

    private:
        float m_size;
        float m_textureSize;
};

#endif // TEXTURE_ATLAS_H
