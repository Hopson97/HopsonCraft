#ifndef TEXTURE_ATLAS_H_INCLUDED
#define TEXTURE_ATLAS_H_INCLUDED

#include "Texture.h"

#include <vector>

#include "../Glm_Common.h"

namespace Texture
{
    class Atlas : public Basic_Texture
    {
        public:
            Atlas(const std::string& textureName, GLuint size, GLuint textureSize);

            std::vector<GLfloat> getTextureCoords (const Vector2& location) const;

        private:
            const GLuint m_size;
            const GLuint m_textureSize;
    };
}

#endif // TEXTURE_ATLAS_H_INCLUDED
