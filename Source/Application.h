#ifndef APPLICATION_H
#define APPLICATION_H

#include <SFML/System/Clock.hpp>

#include "World.h"

class Application
{
    public:
        Application     ();

        void runLoop    ();

    private:
        sf::Clock m_appTimer;


    public:
        constexpr static float FIXED_UPDATE_TIME = 0.00833333; //120 updates a second

        World m_world;
};

#endif // APPLICATION_H
