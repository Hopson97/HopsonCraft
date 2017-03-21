#ifndef BUTTON_H
#define BUTTON_H

#include <functional>

#include "Component.h"

namespace GUI
{
    class Button : public Component
    {
        public:
            Button(const std::string& text,
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
    };
}

#endif // BUTTON_H
