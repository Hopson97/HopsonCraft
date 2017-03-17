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

        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        m_simpleRenderer.update(camera);

        m_chunkRenderer .update (camera);

        //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        m_sfmlRenderer.update ();


        Display::update();
    }

    void Master::draw(const Chunklet& chunklet)
    {
        /*
        if (chunklet.getMesh().getSolidMesh().getFacesCount() > 0)
        {
            m_chunkRenderer .draw(chunklet);
        }
        if (chunklet.getMesh().getLiquidMesh().getFacesCount() > 0)
        {
            m_liquidRenderer.draw(chunklet);
        }
        */
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
