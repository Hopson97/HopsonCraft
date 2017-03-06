#ifndef FRAMEBUFFER_OBJECT_H
#define FRAMEBUFFER_OBJECT_H

//#include "../OpenGL/Glew/glew.h"

#include <GL/glew.h>

#include "../Texture/Texture.h"
#include "../Model/Model.h"

class Framebuffer_Object
{
    public:
        Framebuffer_Object();
        ~Framebuffer_Object();

        void bindFramebuffer();
        void unbind();

        void clear();

        void bindTexture();

    private:
        GLuint  m_fbo = 0;
        GLuint  m_rbo = 0;
        Texture m_textureAttatchment;

        GLuint txr;
};

#endif // FRAMEBUFFER_OBJECT_H
