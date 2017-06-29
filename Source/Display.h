#ifndef DISPLAY_H_INCLUDED
#define DISPLAY_H_INCLUDED

#include <SFML/Graphics.hpp>

namespace sf
{
    class Window;
}

class Display
{
    public:
        Display()       noexcept;

        void close()    noexcept;

        void clear()    noexcept;
        void update()   noexcept;

        bool isOpen()   noexcept;

        sf::RenderWindow& get() noexcept;

        void sfDraw(const sf::Drawable& drawable) noexcept;

    private:
        sf::ContextSettings getContextSettings() noexcept;

        sf::RenderWindow window;
};

//Meyer's Singleton
Display& getDisplay() noexcept;


#endif // DISPLAY_H_INCLUDED
