#include "Cube_Map.h"

#include <SFML/Graphics/Image.hpp>

namespace Texture
{
    void Cube_Map::load(const std::array<std::string, 6>& textureFiles)
    {
        glGenTextures(1, &m_textureID);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureID);

        for (int i = 0; i < 6; i++)
        {
            sf::Image image;
            image.loadFromFile(textureFiles[i]);
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                         0,
                         GL_RGB,
                         image.getSize().x,
                         image.getSize().y,
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
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    }

}
