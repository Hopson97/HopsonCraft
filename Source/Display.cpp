#include "Display.h"

#include <memory>
#include <SFML/Graphics.hpp>
#include <GL/glew.h>


Display& Display::get()
{
    static Display d;
    return d;
}

Display::Display()
:   m_window  {   sf::VideoMode::getDesktopMode(),
                "HopsonCraft - 'V4'",
                sf::Style::Fullscreen,
                getContextSettings()
            }
{
    glewInit();
    glewExperimental = GL_TRUE;
    glViewport(0, 0, getRaw().getSize().x, getRaw().getSize().y);

    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

sf::ContextSettings Display::getContextSettings()
{
    sf::ContextSettings contextSettings;
    contextSettings.depthBits = 24;
    contextSettings.stencilBits = 8;
    contextSettings.antialiasingLevel = 0;
    contextSettings.majorVersion = 3;
    contextSettings.minorVersion = 3;
    /*
        return sf::ContextSettings
        {
            24, //Depth Bits
            8,  //Stencil Bits
            0,  //Anti Alias Level
            3,  //OpenGL Major Version
            3,  //OpenGL Minor Version
            sf::ContextSettings::Attribute::Default, //Attribute Flag
            false   //sRGB Capable
        };
    */
    return contextSettings;
}


void Display::close()
{
    m_window.close();
}

void Display::clear()
{
    glClearColor(0.1, 0.5, 1.0, 1.0);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
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


