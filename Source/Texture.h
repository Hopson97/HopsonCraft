#ifndef TEXTURE_H
#define TEXTURE_H

#include "OpenGL/GLEW/glew.h"
#include "OpenGL/GLM/glm_transformations.h"

#include <string>
#include <vector>

class Texture
{
    public:
        Texture     (const std::string& textureFileName);
        Texture     () = default;
        ~Texture    ();

        void create (const std::string& textureFileName);

        void bind() const;

    private:
        GLuint m_textureId = 0;
};

class Texture_Atlas
{
    public:
        Texture_Atlas (const std::string& textureFileName, size_t imageSize, size_t textureSize);

        std::vector<GLfloat> getTextureCoords (const Vector2& location) const;

        void bind() const;

    private:
        Texture m_texture;

        size_t m_imageSize;
        size_t m_textureSize;
};

#endif // TEXTURE_H
