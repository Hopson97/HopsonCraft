#include "Framebuffer_Object.h"

#include <iostream>
#include <vector>

#include "../Util/Display.h"
#include "../D_Settings.h"

namespace
{
    std::vector<GLfloat> quadVerticies =
    {
         1, -1, 0,
         1,  1, 0,
        -1,  1, 0,

        -1,  1, 0,
        -1, -1, 0,
         1, -1, 0
    };

    std::vector<GLfloat> quadTextureCoords
    {
        1, 0,
        1, 1,
        0, 1,

        0, 1,
        0, 0,
        1, 0
    };

GLuint generateAttachmentTexture(GLboolean depth, GLboolean stencil)
{
    // What enum to use?
    GLenum attachment_type;
    if(!depth && !stencil)
        attachment_type = GL_RGB;
    else if(depth && !stencil)
        attachment_type = GL_DEPTH_COMPONENT;
    else if(!depth && stencil)
        attachment_type = GL_STENCIL_INDEX;

    //Generate texture ID and load texture data
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    if(!depth && !stencil)
        glTexImage2D(GL_TEXTURE_2D, 0, attachment_type, Display::get().getSize().x, Display::get().getSize().y, 0, attachment_type, GL_UNSIGNED_BYTE, NULL);
    else // Using both a stencil and depth test, needs special format arguments
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, Display::get().getSize().x, Display::get().getSize().y, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    return textureID;
}

}


Framebuffer_Object::Framebuffer_Object()
{
    //FrameBuffer
    glGenFramebuffers(1, &m_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

    //Texture attachement
    txr = generateAttachmentTexture(false, false);
    glFramebufferTexture2D(GL_FRAMEBUFFER,
                           GL_COLOR_ATTACHMENT0,
                           GL_TEXTURE_2D,
                           txr,
                           0);
    //RenderBuffer
    glGenRenderbuffers(1, &m_rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
    glRenderbufferStorage(GL_RENDERBUFFER,
                          GL_DEPTH24_STENCIL8,
                          Display::get().getSize().x,
                          Display::get().getSize().y);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER,
                              GL_DEPTH_STENCIL_ATTACHMENT,
                              GL_RENDERBUFFER,
                              m_rbo);
    //Unbind
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	    std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    m_quad.addData(quadVerticies, quadTextureCoords);
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
    glBindTexture(GL_TEXTURE_2D, txr);

    glDrawArrays(GL_TRIANGLES, 0, m_quad.getVertexCount());
}


void Framebuffer_Object::clear()
{
    bind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(Settings::SKY_RED, Settings::SKY_GREEN, Settings::SKY_BLUE, 1.0);
}

