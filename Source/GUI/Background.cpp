#include "Background.h"

#include "../Display.h"
#include "../Renderer/RMaster.h"

namespace GUI
{
    Background::Background(const sf::Texture& texture)
    {

        m_quad.setSize({static_cast<float>(Display::get().getSize().x),
                        static_cast<float>(Display::get().getSize().y)});
        m_quad.setTexture(&texture);
    }

    void Background::draw(Renderer::Master& renderer)
    {
        renderer.draw(m_quad);
    }
}
