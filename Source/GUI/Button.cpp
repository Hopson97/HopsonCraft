#include "Button.h"

#include "../Util/Display.h"
#include "../Renderer/Master_Renderer.h"

namespace GUI
{
    Button::Button(const std::string& text,
                   std::function<void(void)> function)
    :   m_function  (function)
    {
        m_quad.setSize({500, 200});
        m_quad.setTexture(&Component::guiTexture);
        m_quad.setOutlineColor(sf::Color::Black);
        m_quad.setOutlineThickness(2);

        m_text.setFont(Component::guiFont);
        m_text.setString(text);
        m_text.setOutlineColor(sf::Color::Black);
        m_text.setOutlineThickness(2);
        m_text.setCharacterSize(40);
    }

    void Button::input(const sf::Event& e)
    {
        if (e.type == sf::Event::MouseButtonPressed)
        {
            if (m_quad.getGlobalBounds().contains
                (
                    sf::Mouse::getPosition(Display::get()).x,
                    sf::Mouse::getPosition(Display::get()).y)
                )
            {
                if (e.mouseButton.button == sf::Mouse::Left)
                {
                    m_function();
                }
            }
        }
    }

    void Button::update()
    { }

    void Button::draw(Master_Renderer& renderer)
    {
        renderer.draw(m_quad);
        renderer.draw(m_text);
    }

    void Button::setPosition(const sf::Vector2f& position)
    {
        m_quad.setPosition(position);
        m_text.setPosition(position);
        m_text.move(m_quad.getSize().x / 2 - m_text.getLocalBounds().width  / 2,
                    m_quad.getSize().y / 2 - m_text.getLocalBounds().height / 2);
    }

    const sf::Vector2f& Button::getSize() const
    {
        return m_quad.getSize();
    }


}
