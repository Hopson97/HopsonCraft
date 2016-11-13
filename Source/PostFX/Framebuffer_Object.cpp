#include "Framebuffer_Object.h"

#include "../Util/Display.h"

Framebuffer_Object::Framebuffer_Object()
{
    glGenFramebuffers(1, &m_fbo);
    m_textureAttatchment.createEmpty(Display::get().getSize().x, Display::get().getSize().y);
    glFramebufferTexture2D(GL_FRAMEBUFFER,
                           GL_COLOR_ATTACHMENT0,
                           GL_TEXTURE_2D,
                           m_textureAttatchment.getID(),
                           0);
}

Framebuffer_Object::~Framebuffer_Object()
{
    glDeleteFramebuffers(1, &m_fbo);
}

void Framebuffer_Object::bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
}

void Framebuffer_Object::unbind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
