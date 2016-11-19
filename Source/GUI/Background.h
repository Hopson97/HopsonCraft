#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SFML/Graphics.hpp>

class Master_Renderer;

namespace GUI
{
    class Background
    {
        public:
            Background(const std::string& name);

            void draw (Master_Renderer& renderer);

        private:
            sf::Texture         m_texture;
            sf::RectangleShape  m_quad;
    };

}

#endif // BACKGROUND_H
