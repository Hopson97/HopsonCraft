#include "CubeTexture.h"

#include <SFML/Graphics/Image.hpp>

namespace Texture
{
    /**
        ORDER:
            right
            left
            top
            bottom
            back
            front
    **/
    void CubeTexture::loadFromFile(std::array<std::string, 6>&& fileNames)
    {
        glGenTextures   (1, &m_textureID);
        glBindTexture   (GL_TEXTURE_CUBE_MAP, m_textureID);
        glActiveTexture (GL_TEXTURE0);

        auto val = GL_TEXTURE_CUBE_MAP_POSITIVE_X;

        for (int i = 0; i < 6; i++)
        {
            sf::Image image;
            image.loadFromFile(fileNames[i]);

            auto current = val + i;
            auto size    = image.getSize();

            glTexImage2D(current,
                         0,
                         GL_RGB,
                         size.x, size.y,
                         0,
                         GL_RGB,
                         GL_UNSIGNED_BYTE,
                         image.getPixelsPtr());
        }

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    }

    void CubeTexture::bind() const
    {
        glBindTexture (GL_TEXTURE_CUBE_MAP, m_textureID);
    }
}


