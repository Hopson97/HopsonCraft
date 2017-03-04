#include "RMaster.h"

#include "../Display.h"

#include <iostream>

namespace Renderer
{
    void Master::clear()
    {
        Display::clear();
    }

    void Master::update(const Camera& camera)
    {
        m_chunkRenderer.update  (camera);

        Display::update();
    }

    void Master::draw(const Chunklet& chunklet)
    {
        m_chunkRenderer.draw(chunklet);
    }


}
