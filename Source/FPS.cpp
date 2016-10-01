#include "FPS.h"

#include <string>
#include <iostream>



void FPS :: update ()
{

    float fpsThisFrame = getFPS( fpsClock.restart() );
    frameTimes      += fpsThisFrame;

    fpsCount ++;

    if ( fpsClock2.getElapsedTime().asSeconds() >= 1.5 ) {
        float fps = frameTimes / fpsCount;
        printFPS ( fps );
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

void FPS :: printFPS ( float framesPerSecond )
{
    std::cout << framesPerSecond << std::endl;
}
