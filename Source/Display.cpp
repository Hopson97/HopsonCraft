#include "Display.h"

#include <memory>
#include <SFML/Graphics.hpp>
#include "glad/glad.h"


Display& Display::get()
{
    static Display d;
    return d;
}

Display::Display()
{
    sf::ContextSettings contextSettings;
    contextSettings.depthBits = 24;
    contextSettings.stencilBits = 8;
    contextSettings.antialiasingLevel = 0;
    contextSettings.majorVersion = 3;
    contextSettings.minorVersion = 3;

    m_window.create(sf::VideoMode::getDesktopMode(),
                    "HopsonCraft",
                    sf::Style::Fullscreen,
                    contextSettings);
    gladLoadGL();
    glViewport(0, 0, getRaw().getSize().x, getRaw().getSize().y);

    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Display::close()
{
    m_window.close();
}

void Display::update()
{
    m_window.display();
}

bool Display::isOpen()
{
    return m_window.isOpen();
}

sf::RenderWindow& Display::getRaw()
{
    return m_window;
}

void Display::sfDraw(const sf::Drawable& drawable)
{
    m_window.draw(drawable);
}


