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

        GLuint getId () const;

        ~Texture ();

    private:
        GLuint m_textureID;
};

#endif // TEXTURE_H
