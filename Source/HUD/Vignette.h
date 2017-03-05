#ifndef VIGNETTE_H_INCLUDED
#define VIGNETTE_H_INCLUDED

#include <SFML/Graphics.hpp>

namespace Renderer
{
    class Master;
}

class Vignette
{
    public:
        Vignette();

        void draw(Renderer::Master& renderer);

    private:
        sf::RectangleShape m_sprite;
};

#endif // VIGNETTE_H_INCLUDED
