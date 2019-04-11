#include "MasterRenderer.h"

#include "../Display.h"
#include "../World/Block/BlockDatabase.h"

#include "../Maths/Matrix.h"

#include "../Camera.h"

void MasterRenderer::update(const Camera& camera)
{
    glClearColor(0.1, 0.5, 1.0, 1.0);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    BlockDatabase::get().getTextureAtlas().bind();

    glEnable(GL_DEPTH_TEST);
    m_simpleRenderer.update(camera);

    glDisable(GL_DEPTH_TEST);
    //m_sfmlRenderer.update ();

    Display::get().update();
}

void MasterRenderer::draw(const sf::Drawable& drawable)
{
    m_sfmlRenderer.draw(drawable);
}

void MasterRenderer::draw(const Cube& cube)
{
    m_simpleRenderer.draw(cube);
}

