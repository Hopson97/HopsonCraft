#ifndef CROSSHAIR_H_INCLUDED
#define CROSSHAIR_H_INCLUDED

#include <SFML/Graphics.hpp>

class MasterRenderer;

class Crosshair
{
    public:
        enum Mode
        {
            Reg,
            Hit
        };

        Crosshair();

        void draw(MasterRenderer& renderer) noexcept;
        void setMode(Mode mode) noexcept;

    private:
        sf::RectangleShape m_sprite;
};

#endif // CROSSHAIR_H_INCLUDED
