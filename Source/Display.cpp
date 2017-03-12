#include "Display.h"

#include <memory>
#include <SFML/Graphics.hpp>
#include <GL/glew.h>

namespace Display
{
    std::unique_ptr<sf::RenderWindow> window;

    void deactiveate()
    {
        window->setActive(false);
    }

    void activate()
    {
        window->setActive(true);
    }


    void init()
    {
        sf::ContextSettings settings;
        settings.depthBits = 24;
        settings.stencilBits = 8;
        settings.antialiasingLevel = 0;
        settings.majorVersion = 3;
        settings.minorVersion = 0;

        window = std::make_unique<sf::RenderWindow>(sf::VideoMode::getDesktopMode(),
                                                    "Window",
                                                    sf::Style::Close,
                                                    settings);
        glewInit();
        glViewport(0, 0, get().getSize().x, get().getSize().y);

        glEnable    (GL_DEPTH_TEST);
        glEnable    (GL_CULL_FACE);

        glCullFace  (GL_BACK);

        window->setMouseCursorVisible(false);
    }

    void close()
    {
        window->close();
    }

    void clear()
    {
        glClearColor(0.2, 0.5, 1.0, 1.0);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    }

    void update()
    {
        window->display();
    }

    void checkForClose()
    {
        sf::Event e;
        while (window->pollEvent(e))
        {
            if (e.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                close();
            }
        }
    }

    bool isOpen()
    {
        return window->isOpen();
    }

    sf::RenderWindow& get()
    {
        return *window;
    }

    void sfDraw(const sf::Drawable& drawable)
    {
        window->draw(drawable);
    }

}












