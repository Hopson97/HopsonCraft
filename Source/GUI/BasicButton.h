#ifndef BASICBUTTON_H_INCLUDED
#define BASICBUTTON_H_INCLUDED

#include "Button.h"

namespace GUI
{
    class BasicButton : public Button
    {
        public:
            BasicButton(const std::string& text,
                   std::function<void(void)> function);

            void onClick()      override;
            void onMouseTouch() override;
            void onNoInteract() override;

            void draw   (MasterRenderer& renderer) noexcept override;

            void setPosition (const sf::Vector2f& position) override;
            const sf::Vector2f getSize () const             override;

        private:
            std::function<void(void)> m_function;
            sf::RectangleShape  m_quad;
            sf::Text            m_text;
    };
}

#endif // BASICBUTTON_H_INCLUDED
