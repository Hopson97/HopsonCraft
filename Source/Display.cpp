#include "Display.h"

#include <memory>
#include <SFML/Graphics.hpp>
#include <GL/glew.h>

namespace Display
{
    sf::RenderWindow window;

    namespace
    {
        void initOpenGL()
        {
            glewInit();
            glewExperimental = GL_TRUE;
            glViewport(0, 0, get().getSize().x, get().getSize().y);

            glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }
    }

    void init()
    {
        sf::ContextSettings settings;
        settings.depthBits          = 24;
        settings.stencilBits        = 8;
        settings.antialiasingLevel  = 0;
        settings.majorVersion       = 3;
        settings.minorVersion       = 3;


        window.create(sf::VideoMode::getDesktopMode(),
                     "HopsonCraft - 'V4'",
                     sf::Style::Fullscreen,
                     settings);
        initOpenGL();
    }

    void close()
    {
        window.close();
    }

    void clear()
    {
        glClearColor(0.1, 0.5, 1.0, 1.0);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    }

    void update()
    {
        window.display();
    }

    bool isOpen()
    {
        return window.isOpen();
    }

    sf::RenderWindow& get()
    {
        return window;
    }

    void sfDraw(const sf::Drawable& drawable)
    {
        window.draw(drawable);
    }

}












