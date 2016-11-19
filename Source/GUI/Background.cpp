#include "Background.h"

#include "../Util/Display.h"
#include "../Renderer/Master_Renderer.h"

namespace GUI
{
    Background::Background(const std::string& name)
    {
        m_texture.loadFromFile("Data/Images/" + name + ".png");

        m_quad.setSize({static_cast<float>(Display::get().getSize().x),
                        static_cast<float>(Display::get().getSize().y)});
        m_quad.setTexture(&m_texture);
    }

    void Background::draw(Master_Renderer& renderer)
    {
        renderer.processSfDrawable(m_quad);
    }
}
