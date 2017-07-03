#include "Display.h"

#include <memory>
#include <SFML/Graphics.hpp>
#include <GL/glew.h>


Display& getDisplay() noexcept
{
    static Display d;
    return d;
}

Display::Display() noexcept
:   window  {   sf::VideoMode::getDesktopMode(),
                "HopsonCraft - 'V4'",
                sf::Style::Fullscreen,
                getContextSettings()
            }
{
    glewInit();
    glewExperimental = GL_TRUE;
    glViewport(0, 0, get().getSize().x, get().getSize().y);

    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

sf::ContextSettings Display::getContextSettings() noexcept
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


void Display::close() noexcept
{
    window.close();
}

void Display::clear() noexcept
{
    glClearColor(0.1, 0.5, 1.0, 1.0);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

void Display::update() noexcept
{
    window.display();
}

bool Display::isOpen() noexcept
{
    return window.isOpen();
}

sf::RenderWindow& Display::get() noexcept
{
    return window;
}

void Display::sfDraw(const sf::Drawable& drawable) noexcept
{
    window.draw(drawable);
}


