#ifndef VIGNETTE_H_INCLUDED
#define VIGNETTE_H_INCLUDED

#include <SFML/Graphics.hpp>

class MasterRenderer;


class Vignette
{
    public:
        Vignette();

        void draw(MasterRenderer& renderer);

    private:
        sf::RectangleShape m_sprite;
};

#endif // VIGNETTE_H_INCLUDED
