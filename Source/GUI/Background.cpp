#include "Background.h"

#include "../Display.h"
#include "../Renderer/MasterRenderer.h"

namespace GUI
{
    Background::Background(const sf::Texture& texture)
    {

        m_quad.setSize({static_cast<float>(Display::get().getRaw().getSize().x),
                        static_cast<float>(Display::get().getRaw().getSize().y)});
        m_quad.setTexture(&texture);
    }

    void Background::draw(MasterRenderer& renderer) noexcept
    {
        renderer.draw(m_quad);
    }
}
