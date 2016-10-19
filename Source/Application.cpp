#include "Application.h"

#include <iostream>

#include "Util/Window.h"
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

    while ( Window::isOpen() )
    {
        Window::clear( 0.2, 0.2, 0.8);

        float dt = dtClock.restart().asSeconds();

        m_world.update( dt );

        m_world.draw();

        Window::update();
        Window::checkForClose();
        fpsCheck.update();
    }
}
