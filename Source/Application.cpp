#include "Application.h"

#include <iostream>

#include "Display.h"
#include "Util/Frames_Per_Second_Checker.h"

#include "Chunk/Chunk.h"
#include "Texture_Atlas.h"//
#include "Texture.h"
#include "Loader.h"

Application::Application()
{ }

void Application :: runLoop ()
{
    Frames_Per_Second_Checker fpsCheck;
    sf::Clock dtClock;

    sf::Clock test;

    while ( Display::isOpen() )
    {
        Display::clear();

        float dt = dtClock.restart().asSeconds();

        m_world.update( dt );

        m_world.draw();

        Display::update();
        Display::checkForClose();
        fpsCheck.update();
    }
}
