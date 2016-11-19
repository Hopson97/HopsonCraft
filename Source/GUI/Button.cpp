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

        m_text.setFont(Component::guiFont);
        m_text.setString(text);
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
        renderer.processSfDrawable(m_quad);
        renderer.processSfDrawable(m_text);
    }

    void Button::setPosition(const sf::Vector2f& position)
    {
        m_quad.setPosition(position);
        m_text.setPosition(position);
    }

    const sf::Vector2f& Button::getSize() const
    {
        return m_quad.getSize();
    }


}
