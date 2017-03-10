#ifndef CROSSHAIR_H_INCLUDED
#define CROSSHAIR_H_INCLUDED

#include <SFML/Graphics.hpp>

namespace Renderer
{
    class Master;
}

class Crosshair
{
    public:
        enum Mode
        {
            Reg,
            Hit
        };

        Crosshair();

        void draw(Renderer::Master& renderer);
        void setMode(Mode mode);

    private:
        sf::RectangleShape m_sprite;
};

#endif // CROSSHAIR_H_INCLUDED
