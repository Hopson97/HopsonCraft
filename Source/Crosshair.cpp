#include "Crosshair.h"

#include "Util/Display.h"

#include "Renderer/Master_Renderer.h"

Crosshair::Crosshair()
{
    loadTextures();

    m_quad.setSize({SIZE, SIZE});

    m_quad.setTexture   (&m_crossTexture);
    m_quad.setPosition  (Display::get().getSize().x / 2 - SIZE / 2,
                         Display::get().getSize().y / 2 - SIZE / 2);
}

void Crosshair::draw(Master_Renderer& renderer)
{
    renderer.draw(m_quad);
}


void Crosshair::loadTextures()
{
    m_crossTexture.loadFromFile("Data/Images/Crosshair.png");
}

