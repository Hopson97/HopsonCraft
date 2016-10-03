#include "FPS.h"

#include <string>
#include <iostream>

#include "Window.h"

FPS :: FPS ()
{
    font.loadFromFile( "Data/Fonts/rs.ttf" );
    text.setFont( font );
    text.setCharacterSize( 20 );
}

void FPS :: update ()
{
    float fpsThisFrame = getFPS( fpsClock.restart() );
    frameTimes      += fpsThisFrame;

    fpsCount ++;

    if ( fpsClock2.getElapsedTime().asSeconds() >= 1.3 ) {
        float fps = frameTimes / fpsCount;
        setFPS ( fps );
        frameTimes  = 0;
        fpsCount    = 0;
        fpsClock2.restart();
        frameCount ++;;
    }
}

float FPS :: getFPS( const sf::Time& time )
{
    return (1000000.0f / time.asMicroseconds());
}

void FPS :: setFPS ( float framesPerSecond )
{
    std::cout << "Current FPS: " << framesPerSecond << std::endl;
    text.setString( "FPS: " + std::to_string( framesPerSecond ) );
}


void FPS::drawFPS()
{
    Window::sfDraw( text );
}
