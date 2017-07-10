#include "RMaster.h"

#include "../Display.h"
#include "../World/Block/BlockDatabase.h"

#include "../Maths/Matrix.h"

#include "../Camera.h"

namespace Renderer
{
    void Master::clear()
    {
        Display::get().clear();
    }

    void Master::update(const Camera& camera)
    {
        Block::Database::get().getTextureAtlas().bind();

        glEnable(GL_DEPTH_TEST);
        m_simpleRenderer.update(camera);
        m_skyBoxRenderer.update(camera);

        glDisable(GL_DEPTH_TEST);
        m_sfmlRenderer.update ();

        Display::get().update();
    }

    void Master::draw(const sf::Drawable& drawable)
    {
        m_sfmlRenderer.draw(drawable);
    }

    void Master::draw(const Cube& cube)
    {
        m_simpleRenderer.draw(cube);
    }

    void Master::draw(const Texture::CubeTexture& tex)
    {
        m_skyBoxRenderer.draw(tex);
    }

}
