#include "Texture.h"

#include <SFML/Graphics/Image.hpp>

namespace Texture
{
    void Basic_Texture::load(const std::string& fileName)
    {
        std::string filePath = "Data/Textures/" + fileName + ".png";

        sf::Image image;
        image.loadFromFile(filePath);

        glGenTextures(1, &m_textureID);
        glBindTexture(GL_TEXTURE_2D, m_textureID);

        glTexImage2D(GL_TEXTURE_2D,
                     0,
                     GL_RGBA,
                     image.getSize().x,
                     image.getSize().y,
                     0,
                     GL_RGBA,
                     GL_UNSIGNED_BYTE,
                     image.getPixelsPtr());

        //Check the description, I couldn't come up with a quick explaination for these
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Basic_Texture::bind()
    {
        glBindTexture(GL_TEXTURE_2D, m_textureID);
    }

    void Basic_Texture::unbind()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }


}
