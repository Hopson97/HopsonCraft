#ifndef CUBE_MAP_H_INCLUDED
#define CUBE_MAP_H_INCLUDED

#include <array>
#include <string>
#include <GL/glew.h>

#include "../Glm_Common.h"

namespace Texture
{

    class Cube_Map
    {
        public:
            void load(const std::array<std::string, 6>& textureFiles);

        private:
            GLuint m_textureID;
    };

}

#endif // CUBE_MAP_H_INCLUDED
