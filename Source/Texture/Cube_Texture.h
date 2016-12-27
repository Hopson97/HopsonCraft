#ifndef CUBE_TEXTURE_H_INCLUDED
#define CUBE_TEXTURE_H_INCLUDED

#include <vector>
#include <string>

#include <GL/glew.h>

class Cube_Texture
{
    public:
        /**
        *  @brief  Class for a cube map texture
        *  @param  list of file names for the texture
        *   In oder ->
        *       Right
        *       Left
        *       Top
        *       Bottom
        *       Back
        *       Front
        */
        Cube_Texture(const std::vector<std::string> fileNames);
        ~Cube_Texture();

        void bind();
        void unbind();

    private:
        GLuint m_id;
};

#endif // CUBE_TEXTURE_H_INCLUDED
