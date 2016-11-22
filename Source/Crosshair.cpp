#include "Crosshair.h"

#include "Util/Display.h"

#include "Renderer/Master_Renderer.h"

Crosshair::Crosshair()
{
    loadTextures();

    m_quad.setSize({SIZE, SIZE});

    m_quad.setPosition  (Display::get().getSize().x / 2 - SIZE / 2,
                         Display::get().getSize().y / 2 - SIZE / 2);

    showRegularTexture();
}

void Crosshair::draw(Master_Renderer& renderer)
{
    renderer.draw(m_quad);
}

void Crosshair::showMiningTexture()
{
    m_quad.setTexture(&m_miningTexture);
}

void Crosshair::showRegularTexture()
{
    m_quad.setTexture(&m_crossTexture);
}



void Crosshair::loadTextures()
{
    static const std::string path = "Data/Images/Crosshairs/";

    m_crossTexture.loadFromFile (path + "Crosshair.png");
    m_miningTexture.loadFromFile(path + "Mining.png");
}

