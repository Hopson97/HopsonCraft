#include "SFML_Renderer.h"

#include "../Util/Display.h"

void SFML_Renderer::addSfDrawable(const sf::Drawable& sfDrawable)
{
    m_drawables.push_back(&sfDrawable);
}

void SFML_Renderer::render()
{
    Display::prepareSfDraw();

    for(auto& drawable : m_drawables)
        Display::sfDraw(*drawable);

    Display::endSfDraw();

    m_drawables.clear();
}
