#include "Framebuffer_Object.h"

#include <iostream>
#include <vector>

#include "../Util/Display.h"
#include "../D_Settings.h"
#include "../Loader.h"

namespace
{
    std::vector<GLfloat> quadVerticies =
    {
         1.0f,  1.0f,
        -1.0f, -1.0f,
         1.0f, -1.0f,

        -1.0f,  1.0f,
         1.0f, -1.0f,
         1.0f,  1.0f,
    };

    std::vector<GLfloat> quadTextureCoords
    {
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,

        0.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 1.0f
    };
}

Framebuffer_Object::Framebuffer_Object()
{
    //FrameBuffer
    glGenFramebuffers(1, &m_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    m_textureAttatchment.createEmpty(Display::get().getSize().x, Display::get().getSize().y);
    glFramebufferTexture2D(GL_FRAMEBUFFER,
                           GL_COLOR_ATTACHMENT0,
                           GL_TEXTURE_2D,
                           m_textureAttatchment.getID(),
                           0);
    //RenderBuffer
    glGenRenderbuffers(1, &m_rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
    glRenderbufferStorage(GL_RENDERBUFFER,
                          GL_DEPTH24_STENCIL8,
                          Display::get().getSize().x,
                          Display::get().getSize().y);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER,
                              GL_DEPTH_STENCIL_ATTACHMENT,
                              GL_RENDERBUFFER,
                              m_rbo);
    //Unbind

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	    std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    m_quad.addData(Loader::loadArrayMesh(quadVerticies, quadTextureCoords));
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

void Framebuffer_Object::draw()
{
    m_quad.bind();
    m_textureAttatchment.bind();

    glDrawArrays(GL_TRIANGLES, 0, m_quad.getVertexCount());
}


void Framebuffer_Object::clear()
{
    bind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(Settings::SKY_RED, Settings::SKY_GREEN, Settings::SKY_BLUE, 1.0);
}

