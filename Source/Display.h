#ifndef DISPLAY_H_INCLUDED
#define DISPLAY_H_INCLUDED

#include <SFML/Graphics.hpp>

namespace sf
{
    class Window;
}

namespace Display
{
    constexpr int WIDTH = 1280;
    constexpr int HEIGHT = 720;

    void init();
    void close();

    void clear();
    void update();

    void checkForClose();

    bool isOpen();

    const sf::Window& get();

    void sfDraw(const sf::Drawable& drawable);
}

#endif // DISPLAY_H_INCLUDED
