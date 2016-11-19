#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SFML/Graphics.hpp>

class Master_Renderer;

namespace GUI
{
    class Background
    {
        public:
            Background(const sf::Texture& texture);

            void draw (Master_Renderer& renderer);

        private:
            sf::RectangleShape  m_quad;
    };

}

#endif // BACKGROUND_H
