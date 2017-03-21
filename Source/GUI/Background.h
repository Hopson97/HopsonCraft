#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SFML/Graphics.hpp>

namespace Renderer { class Master; }

namespace GUI
{
    class Background
    {
        public:
            Background(const sf::Texture& texture);

            void draw (Renderer::Master& renderer);

        private:
            sf::RectangleShape  m_quad;
    };

}

#endif // BACKGROUND_H
