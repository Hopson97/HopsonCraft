#ifndef DISPLAY_H_INCLUDED
#define DISPLAY_H_INCLUDED

#include <SFML/Graphics.hpp>

#include "Util/Singleton.h"

namespace sf
{
    class Window;
}

class Display : public Singleton
{
    public:
        static Display& get();

        void close();

        void update();

        bool isOpen();

        sf::RenderWindow& getRaw();

        void sfDraw(const sf::Drawable& drawable);

    private:
        Display();

        sf::RenderWindow m_window;
};


#endif // DISPLAY_H_INCLUDED
