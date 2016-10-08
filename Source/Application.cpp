#include "Application.h"

#include "Util/Window.h"
#include "Util/Frames_Per_Second_Checker.h"

#include "Chunk.h"
#include "Texture_Atlas.h"
#include "Texture.h"
#include "Loader.h"

Application::Application()
{
}

void Application :: runLoop ()
{
    Frames_Per_Second_Checker fpsCheck;
    m_appTimer.restart();

    sf::Time updateTime = sf::milliseconds( FIXED_UPDATE_TIME );
    sf::Clock updateTimer;
    sf::Clock dtClock;

    while ( Window::isOpen() )
    {
        Window::clear( 0.2, 0.2, 0.8);

        float dt = dtClock.restart().asSeconds();

        m_world.update( dt );

        updateTimer.restart();

        m_world.draw();

        Window::update();
        Window::checkForClose();
        fpsCheck.update();
    }
}
