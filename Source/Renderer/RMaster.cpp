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
        Block::Database::get().textures.bind();

        m_simpleRenderer.update(camera);
        m_chunkRenderer .update (camera);
        m_sfmlRenderer.update ();


        Display::update();
    }

    void Master::draw(const Chunk::Section& section)
    {
        m_chunkRenderer.draw(section);
    }

    void Master::draw(const sf::Drawable& drawable)
    {
        m_sfmlRenderer.draw(drawable);
    }

    void Master::draw(const Quad& quad)
    {
        m_simpleRenderer.draw(quad);
    }

}
