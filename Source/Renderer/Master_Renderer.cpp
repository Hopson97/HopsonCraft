#include "Master_Renderer.h"

#include "../D_Settings.h"
#include "../Util/Display.h"

namespace
{
    std::vector<GLfloat> quadVerticies =
    {
         1, -1, 0,
         1,  1, 0,
        -1,  1, 0,
        -1, -1, 0,
    };

    std::vector<GLfloat> quadTextureCoords
    {
        1, 0,
        1, 1,
        0, 1,
        0, 0,
    };

    std::vector<GLuint> quadIndices
    {
        0, 1, 2,
        2, 3, 0
    };
}

Master_Renderer::Master_Renderer()
:   m_simpleShader  ("Simple_Vertex",   "Simple_Fragment")
,   m_blueShader    ("Blue_Vertex",     "Blue_Fragment")
{
    m_quad.addData(quadVerticies, quadTextureCoords, quadIndices);
}

void Master_Renderer::clear()
{
    m_framebuffer.clear();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(Settings::SKY_RED, Settings::SKY_GREEN, Settings::SKY_BLUE, 1.0);
}


void Master_Renderer::draw(const Chunk& chunk)
{
    m_chunkRenderer.addChunk    (chunk);
    m_waterRenderer.addChunk    (chunk);
    m_floraRenderer.addChunk    (chunk);
}

void Master_Renderer::draw(const sf::Drawable& sfDrawable)
{
    m_sfmlRenderer.addSfDrawable(sfDrawable);
}

void Master_Renderer::update (const Camera& camera)
{
    //Draw the scene (to the FBO)
    drawScene(camera);

    //Draw to the window wide quad
    drawToQuad();

    //Finally, draw SFML stuff.
    m_sfmlRenderer .render  ();

    Display::update();
}

void Master_Renderer::addPostFX(Post_FX postFx)
{
    switch(postFx)
    {
        case Post_FX::Blue:
            m_postFXPasses.push_back(&m_blueShader);
            break;
    }
}




void Master_Renderer::drawToQuad()
{
    m_framebuffer.bindTexture();
    m_quad.bind();

    for(auto& shader : m_postFXPasses)
    {
        shader->useProgram();
        m_framebuffer.unbind();
        m_simpleShader.useProgram();
        glDrawElements(GL_TRIANGLES,
                       6,
                       GL_UNSIGNED_INT,
                       nullptr);
    }
    m_postFXPasses.clear();


    //Draw to the default context
    m_framebuffer.unbind();
    m_simpleShader.useProgram();
    glDrawElements(GL_TRIANGLES,
                   6,
                   GL_UNSIGNED_INT,
                   nullptr);
}

void Master_Renderer::drawScene(const Camera& camera)
{
    m_framebuffer.bindFramebuffer();

    m_chunkRenderer.render  (camera);
    m_waterRenderer.render  (camera);
    m_floraRenderer.render  (camera);
}
