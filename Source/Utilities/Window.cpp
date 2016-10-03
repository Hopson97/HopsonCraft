#include "Window.h"

#include <memory>
#include <SFML/Graphics.hpp>

#include "../OpenGL/GLEW/glew.h"

namespace Window
{
    namespace
    {
        std::unique_ptr<sf::RenderWindow> m_window;
    }

void create()
{
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 3;
    settings.minorVersion = 0;

    m_window = std::make_unique<sf::RenderWindow>( sf::VideoMode ( WIDTH, HEIGHT ), "MattCraft", sf::Style::Default, settings );

    glewInit();
    glewExperimental = GL_TRUE;

    glViewport( 0, 0, WIDTH, HEIGHT );

    glEnable    ( GL_DEPTH_TEST );
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
    while ( m_window->pollEvent( e ) ) {
        if ( e.type == sf::Event::Closed )  {
            m_window->close();
        }
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



}//Name space Window
