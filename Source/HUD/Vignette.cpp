#include "Vignette.h"

#include "../Display.h"
#include "../Renderer/MasterRenderer.h"
#include "../ResourceManagers/ResourceHolder.h"

Vignette::Vignette()
{
    m_sprite.setSize({(float)Display::get().getRaw().getSize().x,
                      (float)Display::get().getRaw().getSize().y});
    m_sprite.setTexture(&ResourceHolder::getTexure("Vignette"));
}

void Vignette::draw(MasterRenderer& renderer)
{
    renderer.draw(m_sprite);
}
