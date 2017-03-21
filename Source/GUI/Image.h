#ifndef IMAGE_H
#define IMAGE_H

#include "Component.h"

namespace GUI
{
    class Image : public Component
    {
        public:
            Image(const std::string& name, const sf::Vector2f& size = {500, 200});

            void input  (const sf::Event& e)                override;
            void update ()                                  override;
            void draw   (Renderer::Master& renderer)         override;

            void setPosition (const sf::Vector2f& position) override;
            const sf::Vector2f getSize () const             override;

        private:
            sf::Texture m_texture;
            sf::RectangleShape m_quad;
    };
}

#endif // IMAGE_H
