#ifndef TEXT_BOX_H
#define TEXT_BOX_H

#include "Component.h"

namespace GUI
{
    class Text_Box : public Component
    {
        public:
            Text_Box(unsigned maxTextLength,
                     const sf::Vector2f& size,
                     const std::string& labelText,
                     std::string& inputString);

            void input  (const sf::Event& e)                override;
            void update ()                                  override;
            void draw   (Renderer::Master& renderer)         override;

            void setPosition (const sf::Vector2f& position) override;
            const sf::Vector2f getSize () const             override;

        private:
            sf::RectangleShape  m_quad;
            sf::Text            m_text;
            sf::Text            m_label;

            std::string* m_inputtedText;

            unsigned m_maxLength;

            bool m_isActive = false;
    };
}


#endif // TEXT_BOX_H
