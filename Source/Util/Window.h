#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics.hpp>

namespace Window
{
    void create ( const std::string& name   = "Window" );

    void clear  ( float r = 0,
                  float g = 0,
                  float b = 0 );

    void update ();
    void close  ();
    bool isOpen ();

    void prepareSfDraw  ();
    void sfDraw         ( const sf::Drawable& drawable );
    void endSfDraw      ();

    void checkForClose  ();

    float getAspect     ();

    constexpr static int WIDTH  = 1280,
                         HEIGHT = 720;
}

#endif // WINDOW_H
