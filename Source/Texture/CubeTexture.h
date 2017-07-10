#ifndef CUBETEXTURE_H_INCLUDED
#define CUBETEXTURE_H_INCLUDED

#include <array>
#include <string>
#include <GL/glew.h>

namespace Texture
{
    class CubeTexture
    {
        public:
            void loadFromFile(std::array<std::string, 6>&& fileNames);

            void bind() const;

        private:
            GLuint m_textureID;
    };
}

#endif // CUBETEXTURE_H_INCLUDED
