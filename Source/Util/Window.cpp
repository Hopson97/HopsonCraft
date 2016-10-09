#include "Window.h"

#include <memory>
#include <SFML/Graphics.hpp>
#include "../OpenGL/Glew/glew.h"

namespace Window
{
    namespace
    {
        std::unique_ptr<sf::RenderWindow> m_window;//

        void initGL ()
        {
            glewInit();
            glewExperimental = GL_TRUE;

            glViewport  ( 0, 0, WIDTH, HEIGHT );
            glEnable    ( GL_DEPTH_TEST );
            //glEnable    ( GL_CULL_FACE  );
            //glCullFace  ( GL_BACK );
            //glPolygonMode(GL_FRONT, GL_LINE);
            //glPolygonMode(GL_BACK, GL_LINE);
        }
    }

    void create ( const std::string& name )
    {
        sf::ContextSettings settings;
        settings.depthBits = 24;
        settings.stencilBits = 8;
        settings.antialiasingLevel = 4;
        settings.majorVersion = 3;
        settings.minorVersion = 0;

        m_window = std::make_unique<sf::RenderWindow>( sf::VideoMode ( WIDTH, HEIGHT ), name, sf::Style::Close, settings );
        m_window->setMouseCursorVisible( false );

        initGL();
    }

    void clear( float r, float g, float b )
    {
        glClear     ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        glClearColor( r, g, b, 1 );
    }


    void update()
    {
        m_window->display();
    }

    void close()
    {
        m_window->close();
    }

    bool isOpen()
    {
        return m_window->isOpen();
    }

    void checkForClose ()
    {
        sf::Event e;
        while ( m_window->pollEvent( e ) )
        {
            if ( e.type == sf::Event::Closed )
            {
                m_window->close();
            }
        }
        if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Escape ) )
        {
            m_window->close();
        }
    }

    void prepareSfDraw ()
    {
        m_window->pushGLStates();
    }

    void sfDraw( const sf::Drawable& drawable )
    {
        m_window->draw ( drawable );
    }

    void endSfDraw ()
    {
        m_window->popGLStates();
    }

    float getAspect()
    {
        return (float)WIDTH / (float)HEIGHT;
    }

    const sf::RenderWindow& get ()
    {
        return *m_window;
    }
}//Name space Window
