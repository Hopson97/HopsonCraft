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

            void input  (const sf::Event& e);
            void update ();
            void draw   (Master_Renderer& renderer);

            void setPosition (const sf::Vector2f& position);
            const sf::Vector2f& getSize () const;

        private:
            sf::RectangleShape  m_quad;
            sf::Text            m_text;

            std::string* m_inputtedText;

            unsigned m_maxLength;

            bool m_isActive = false;
    };
}


#endif // TEXT_BOX_H
