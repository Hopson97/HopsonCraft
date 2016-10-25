#include "Display.h"
#include "OpenGL/GLEW/glew.h"

#include <memory>
#include <iostream>

namespace Display
{
    namespace
    {
        std::unique_ptr<sf::RenderWindow> window;

        void initGL (const sf::VideoMode& videoMode)
        {
            glewInit();
            glewExperimental = GL_TRUE;

            glEnable    ( GL_DEPTH_TEST );

            glEnable    (GL_BLEND);
            glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            glViewport(0,
                       0,
                       videoMode.width,
                       videoMode.height);
        }
    }

    void create (const std::string& name)
    {
        sf::ContextSettings settings;
        settings.depthBits = 24;
        settings.stencilBits = 8;
        settings.antialiasingLevel = 8;
        settings.majorVersion = 3;
        settings.minorVersion = 0;

        sf::VideoMode videoMode (sf::VideoMode::getDesktopMode());

        window = std::make_unique<sf::RenderWindow>(  videoMode,
                 name,
                 sf::Style::Close,
                 settings);
        window->setMouseCursorVisible(false);
        window->setPosition ({0, 0});
        initGL(videoMode);
    }

    void clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.2, 0.5, 0.9, 1.0);
    }

    void update()
    {
        window->display();
    }

    bool isOpen()
    {
        return window->isOpen();
    }

    void prepareSfDraw ()
    {
        window->pushGLStates();
        glDisable ( GL_DEPTH_TEST );
        //window->resetGLStates();
    }


    void sfDraw(const sf::Drawable& drawable)
    {
        window->draw(drawable);
    }

    void endSfDraw ()
    {
        window->popGLStates();
        glEnable ( GL_DEPTH_TEST );
    }


    const sf::RenderWindow& get()
    {
        return *window;
    }

    float getAspect()
    {
        return (float)window->getSize().x / (float)window->getSize().y;
    }

    void checkForClose()
    {
        sf::Event e;
        while (window->pollEvent(e))
        {
            switch(e.type)
            {
                case sf::Event::Closed:
                    close();
                    break;

                case sf::Event::KeyPressed:
                    if (e.key.code == sf::Keyboard::E)
                    {
                        close();
                        break;
                    }
                default:
                    break;
            }
        }
    }

    void close()
    {
        window->close();
    }
}
