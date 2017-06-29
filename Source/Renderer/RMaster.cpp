#include "RMaster.h"

#include "../Display.h"
#include "../World/Block/BlockDatabase.h"

#include "../Maths/Matrix.h"

#include "../Camera.h"

namespace Renderer
{
    void Master::clear()
    {
        getDisplay().clear();
    }

    void Master::update(const Camera& camera)
    {
        ///@TODO This is starting to feel a bit bad
        ///Another way to do this?
        Block::Database::get().getTextureAtlas().bind();

        glEnable(GL_DEPTH_TEST);
        m_simpleRenderer.update(camera);

        //m_chunkRenderer .update (camera);
        //m_floraRenderer .update (camera);
        //m_liquidRenderer.update (camera);

        glDisable(GL_DEPTH_TEST);
        m_sfmlRenderer.update ();

        getDisplay().update();
    }

    void Master::draw(const Chunk::Section& section)
    {
        //m_chunkRenderer.draw    (section);
        //m_floraRenderer.draw    (section);
        //m_liquidRenderer.draw   (section);
    }

    void Master::draw(const sf::Drawable& drawable)
    {
        m_sfmlRenderer.draw(drawable);
    }

    void Master::draw(const Cube& cube)
    {
        m_simpleRenderer.draw(cube);
    }
}
