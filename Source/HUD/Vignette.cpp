#include "Vignette.h"

#include "../Display.h"
#include "../Renderer/RMaster.h"
#include "../ResourceManagers/ResourceHolder.h"

Vignette::Vignette()
{
    m_sprite.setSize({(float)getDisplay().get().getSize().x,
                      (float)getDisplay().get().getSize().y});
    m_sprite.setTexture(&getResources().textures.get("Vignette"));
}

void Vignette::draw(Renderer::Master& renderer)
{
    renderer.draw(m_sprite);
}
