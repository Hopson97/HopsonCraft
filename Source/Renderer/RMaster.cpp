#include "RMaster.h"

#include "../Display.h"
#include "../World/Block/Block_Database.h"

#include "../Maths/Matrix_Maths.h"

#include "../Camera.h"

namespace Renderer
{
    void Master::clear()
    {
        Display::clear();
    }

    void Master::update(const Camera& camera)
    {
        ///@TODO This is starting to feel a bit bad
        ///Another way to do this?
        Block::Database::get().getTextureAtlas().bind();

        glEnable(GL_DEPTH_TEST);
        m_simpleRenderer.update(camera);

        m_chunkRenderer .update (camera);
        m_floraRenderer .update (camera);
        m_liquidRenderer.update (camera);

        m_hitboxRenderer.update (camera);

        glDisable(GL_DEPTH_TEST);
        m_sfmlRenderer.update ();

        Display::update();
    }

    void Master::draw(const Chunk::Section& section)
    {
        m_chunkRenderer.draw    (section);
        m_floraRenderer.draw    (section);
        m_liquidRenderer.draw   (section);
    }

    void Master::draw(const sf::Drawable& drawable)
    {
        m_sfmlRenderer.draw(drawable);
    }

    void Master::draw(const Quad& quad)
    {
        m_simpleRenderer.draw(quad);
    }

    void Master::draw(const Vector3& location)
    {
        m_hitboxRenderer.draw(location);
    }


}
