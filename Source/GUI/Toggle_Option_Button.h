#ifndef TOGGLE_OPTION_BUTTON_H_INCLUDED
#define TOGGLE_OPTION_BUTTON_H_INCLUDED

#include "Component.h"

namespace GUI
{
    class Toggle_Option_Button : public Component
    {
        public:
            Toggle_Option_Button(std::string&& title,
                                 std::vector<std::string>&& order,
                                 std::vector<int32_t>&&     values,
                                 int32_t& option);

            void input  (const sf::Event& e)                override;
            void update ()                                  override;
            void draw   (Renderer::Master& renderer)         override;

            void setPosition (const sf::Vector2f& position) override;
            const sf::Vector2f getSize () const             override;

        private:
            void nextOption();

            sf::RectangleShape  m_quad;
            sf::Text            m_text;

            std::vector<std::string> m_options;
            std::vector<int32_t>     m_optionValues;
            int32_t* mp_option;
            std::string m_label;
            int32_t m_optionIndex = 0;
    };
}

#endif // TOGGLE_OPTION_BUTTON_H_INCLUDED
