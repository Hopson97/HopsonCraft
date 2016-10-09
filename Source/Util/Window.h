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

    const sf::RenderWindow& get ();

    constexpr static int WIDTH  = 1960,
                         HEIGHT = 1080;
}

#endif // WINDOW_H
