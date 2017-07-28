#ifndef TEXTURE_ATLAS_H_INCLUDED
#define TEXTURE_ATLAS_H_INCLUDED

#include <vector>

#include "BasicTexture.h"
#include "../Maths/GLM.h"

class TextureAtlas : public BasicTexture
{
    public:
        TextureAtlas(const std::string& textureName, GLuint size, GLuint textureSize);

        bool loadFromFile(const std::string& textureName, GLuint size, GLuint textureSize);


        std::vector<GLfloat> getTextureCoords (const Vector2& location) const;

    private:
        GLuint m_size;
        GLuint m_textureSize;
};


#endif // TEXTURE_ATLAS_H_INCLUDED
