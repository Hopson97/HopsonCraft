#include "Window.h"

#include <memory>
#include <SFML/Graphics.hpp>
#include "../OpenGL/Glew/glew.h"
#include "D_Settings.h"


namespace Window
{
    namespace
    {
        std::unique_ptr<sf::RenderWindow> m_window;//

        void initGL ()
        {
            glewInit();
            glewExperimental = GL_TRUE;
            glEnable    ( GL_DEPTH_TEST );
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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

        sf::VideoMode m( sf::VideoMode::getDesktopMode() );
        m_window = std::make_unique<sf::RenderWindow>( sf::VideoMode ( m.width, m.height ), name, sf::Style::Fullscreen, settings );
        m_window->setMouseCursorVisible( false );
        m_window->setPosition ( { 0, 0 } );



        initGL();

        glViewport( 0, 0, m.width, m.height );
    }

    void clear( float r, float g, float b )
    {
        glClear     ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        glClearColor(   Settings::SKY_RED,
                        Settings::SKY_GREEN,
                        Settings::SKY_BLUE,
                        1.0
                    );
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

    void setToFullScreen ()
    {

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
