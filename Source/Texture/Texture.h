#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

//#include "../OpenGL/Glew/glew.h"

#include <GL/glew.h>

class Texture
{
    public:
        Texture     () = default;
        Texture     ( const std::string& filePath );

        void loadFromFile ( const std::string& file );
        void createEmpty  (int width, int height);

        void bind   ();
        void unbind ();

        const GLuint& getID () const;

        ~Texture ();

    private:
        void create(int width, int height, const void* data);

        GLuint m_textureID = 0;
};

#endif // TEXTURE_H
