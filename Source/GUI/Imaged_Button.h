#ifndef IMAGED_BUTTON_H
#define IMAGED_BUTTON_H

#include <functional>

#include "Component.h"

namespace GUI
{
    class Imaged_Button : public Component
    {
        public:
            Imaged_Button(const std::string& name, const std::string& text,
                          std::function<void(void)> function);

            void input  (const sf::Event& e)                override;
            void update ()                                  override;
            void draw   (Renderer::Master& renderer)         override;

            void setPosition (const sf::Vector2f& position) override;
            const sf::Vector2f getSize () const             override;

        private:
            std::function<void(void)> m_function;
            sf::RectangleShape  m_quad;
            sf::Text            m_text;

            sf::Texture m_image;
            sf::RectangleShape m_imageRect;
    };
}

#endif // IMAGED_BUTTON_H
