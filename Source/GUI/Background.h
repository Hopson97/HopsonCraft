#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SFML/Graphics.hpp>

class MasterRenderer;

namespace GUI
{
    class Background
    {
        public:
            Background(const sf::Texture& texture);

            void draw (MasterRenderer& renderer) noexcept;

        private:
            sf::RectangleShape  m_quad;
    };

}

#endif // BACKGROUND_H
