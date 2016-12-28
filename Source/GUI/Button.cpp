#include "Button.h"

#include "../Util/Display.h"
#include "../Renderer/Master_Renderer.h"
#include "../D_Settings.h"

namespace GUI
{/*
    Button::Button(const std::string& text,
                   std::function<void(void)> function)
    :   m_function  (function)
    {
        m_quad.setSize({800, 150});
        m_quad.setTexture(&Component::guiTexture);
        m_quad.setOutlineColor(sf::Color::Black);
        m_quad.setOutlineThickness(2);

        initText(m_text, 40, text);
    }

    void Button::input(const sf::Event& e)
    {
        if (touchingMouse(m_quad))
        {
            m_quad.setFillColor({(sf::Uint8)Settings::SKY_RED   * (sf::Uint8)255,
                                 (sf::Uint8)Settings::SKY_GREEN * (sf::Uint8)255,
                                 (sf::Uint8)Settings::SKY_BLUE  * (sf::Uint8)255});
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

    const sf::Vector2f Button::getSize() const
    {
        return m_quad.getSize();
    }

*/
}
