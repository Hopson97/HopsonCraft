#ifndef FRAMEBUFFER_OBJECT_H
#define FRAMEBUFFER_OBJECT_H

#include "../OpenGL/Glew/glew.h"

class Framebuffer_Object
{
    public:
        Framebuffer_Object();
        ~Framebuffer_Object();

        void bind();
        void unbind();

    private:
        GLuint m_fbo = 0;
};

#endif // FRAMEBUFFER_OBJECT_H
