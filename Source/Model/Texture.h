#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

#include "../OpenGL/Glew/glew.h"

class Texture
{
    public:
        Texture     () = default;
        Texture     ( int id );

        void loadFromFile ( const std::string& file );

        void bind   ();
        void unbind ();

        ~Texture ();

    private:
        GLuint m_textureID;
};

#endif // TEXTURE_H
