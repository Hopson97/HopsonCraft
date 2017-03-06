#ifndef TEXTURE_ATLAS_H
#define TEXTURE_ATLAS_H

#include <GL/glew.h>
#include <vector>

#include "../OpenGL/GL_Maths.h"
#include "Texture.h"
#include "../Util/Hasher.h"

namespace std
{
    template<>
    struct hash<Vector2>
    {
        size_t operator() (const Vector2& v) const
        {
            return Hasher::hash(v.x, v.y);
        }
    };
}

class Texture_Atlas : public Texture
{
    public:
        Texture_Atlas(float imageSize, float textureSize, const std::string& file);

        std::vector<GLfloat>& getTextureCoords (const Vector2& location) const;

    private:
        float m_size;
        float m_textureSize;
};

#endif // TEXTURE_ATLAS_H
