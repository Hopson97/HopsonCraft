#ifndef FRAMEBUFFER_OBJECT_H
#define FRAMEBUFFER_OBJECT_H

#include "../OpenGL/Glew/glew.h"
#include "../Texture/Texture.h"
#include "../Model/Model.h"

class Framebuffer_Object
{
    public:
        Framebuffer_Object();
        ~Framebuffer_Object();

        void bind();
        void unbind();

        void clear();

        void draw();

    private:
        GLuint  m_fbo = 0;
        GLuint  m_rbo = 0;
        Texture m_textureAttatchment;

        Model m_quad;
};

#endif // FRAMEBUFFER_OBJECT_H
