#include "Framebuffer_Object.h"

#include "../Util/Display.h"

#include "../Util/Display.h"

Framebuffer_Object::Framebuffer_Object()
{
    glGenFramebuffers(1, &m_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    m_textureAttatchment.createEmpty(Display::get().getSize().x, Display::get().getSize().y);
    m_textureAttatchment.bind();
    glFramebufferTexture2D(GL_FRAMEBUFFER,
                           GL_COLOR_ATTACHMENT0,
                           GL_TEXTURE_2D,
                           m_textureAttatchment.getID(),
                           0);

    glGenRenderbuffers(1, &m_rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, m_fbo);

    glRenderbufferStorage(GL_RENDERBUFFER,
                          GL_DEPTH24_STENCIL8,
                          Display::get().getSize().x,
                          Display::get().getSize().y);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER,
                              GL_DEPTH_STENCIL_ATTACHMENT,
                              GL_RENDERBUFFER,
                              m_rbo);
}

Framebuffer_Object::~Framebuffer_Object()
{
    glDeleteFramebuffers(1, &m_fbo);
    glDeleteRenderbuffers(1, &m_rbo);
}

void Framebuffer_Object::bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
}

void Framebuffer_Object::unbind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
