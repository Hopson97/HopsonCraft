#include "RMaster.h"

#include "../Display.h"
#include "../World/Block/Block_Database.h"

#include <iostream>

namespace Renderer
{
    void Master::clear()
    {
        Display::clear();
    }

    void Master::update(const Camera& camera)
    {
        Block::Database::get().textures.bind();

        m_chunkRenderer .update (camera);
        m_sfmlRenderer  .update ();

        Display::update();
    }

    void Master::draw(const Chunklet& chunklet)
    {
        m_chunkRenderer.draw(chunklet);
    }

    void Master::draw(const sf::Drawable& drawable)
    {
        m_sfmlRenderer.draw(drawable);
    }
}
