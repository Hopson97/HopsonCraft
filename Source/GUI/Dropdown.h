#ifndef DROPDOWN_H
#define DROPDOWN_H

#include "Component.h"

namespace GUI
{
    class Dropdown : public Component
    {
        public:
            Dropdown(int& optionPtr,
                     const std::string& label,
                     const std::vector<std::string>& options);

            void input  (const sf::Event& e)                override;
            void update ()                                  override;
            void draw   (Renderer::Master& renderer)         override;

            void setPosition (const sf::Vector2f& position) override;
            const sf::Vector2f getSize () const             override;

        private:
            bool m_isOpen    = false;
            int* m_optionPtr = nullptr;

            sf::RectangleShape  m_quad;
            sf::Text            m_label;

            std::vector<sf::Text> m_options;
    };
}

#endif // DROPDOWN_H
