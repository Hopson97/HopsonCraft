#include "Button.h"

#include "../Display.h"
#include "../Renderer/RMaster.h"

namespace GUI
{
    Button::Button(const std::string& text,
                   std::function<void(void)> function)
    :   m_function  (function)
    {
        m_quad.setSize({BASE_WIDTH, BASE_HEIGHT});
        m_quad.setTexture(&Component::guiTexture);
        m_quad.setOutlineColor(sf::Color::Black);
        m_quad.setOutlineThickness(4);

        initText(m_text, 24, text);
    }

    void Button::input(const sf::Event& e)
    {
        if (touchingMouse(m_quad))
        {
            m_quad.setFillColor(sf::Color::Blue);
        }
        else
        {
            m_quad.setFillColor(sf::Color::White);
        }

        if(clicked(m_quad, e))
        {
            m_function();
        }
    }

    void Button::update()
    { }

    void Button::draw(Renderer::Master& renderer)
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

    const sf::Vector2f Button::getSize() const
    {
        return m_quad.getSize();
    }


}
