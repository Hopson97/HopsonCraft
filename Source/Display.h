#ifndef DISPLAY_H_INCLUDED
#define DISPLAY_H_INCLUDED

#include <SFML/Graphics.hpp>

namespace sf
{
    class Window;
}

namespace Display
{
    void init();
    void close();

    void clear();
    void update();

    bool isOpen();

    sf::RenderWindow& get();

    void sfDraw(const sf::Drawable& drawable);
}

#endif // DISPLAY_H_INCLUDED
