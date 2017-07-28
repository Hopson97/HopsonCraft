#include "Crosshair.h"

#include "../Display.h"
#include "../Renderer/MasterRenderer.h"
#include "../ResourceManagers/ResourceHolder.h"

Crosshair::Crosshair()
{
    m_sprite.setSize({30, 30});
    auto rect = m_sprite.getLocalBounds();
    m_sprite.setOrigin(rect.left + rect.width / 2.0f,
                       rect.top  + rect.height / 2.0f);

    m_sprite.setTexture (&ResourceHolder::getTexure("Crosshair"));
    m_sprite.setPosition(Display::get().getRaw().getSize().x / 2,
                         Display::get().getRaw().getSize().y / 2);
}

void Crosshair::draw(MasterRenderer& renderer) noexcept
{
    renderer.draw(m_sprite);
}

void Crosshair::setMode(Mode mode) noexcept
{
    switch (mode)
    {
        case Mode::Hit:
            m_sprite.setFillColor(sf::Color::Red);
            break;

        case Mode::Reg:
            m_sprite.setFillColor(sf::Color::White);
            break;
    }
}

