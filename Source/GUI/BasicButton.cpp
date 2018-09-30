#include "BasicButton.h"

#include "../Display.h"
#include "../Renderer/MasterRenderer.h"

#include "../ResourceManagers/ResourceHolder.h"

namespace GUI
{
    BasicButton::BasicButton(const std::string& text,
                   std::function<void(void)> function)
    :   Button      (m_quad)
    ,   m_function  (function)
    {
        m_quad.setSize({BASE_WIDTH, BASE_HEIGHT});
        m_quad.setTexture(&ResourceHolder::getTexure("GUI"));
        m_quad.setOutlineColor(sf::Color::Black);
        m_quad.setOutlineThickness(4);

        initText(m_text, 24, text);
    }


    void BasicButton::onClick()
    {
        m_function();
    }

    void BasicButton::onMouseTouch()
    {
        m_quad.setFillColor(sf::Color::Blue);
    }

    void BasicButton::onNoInteract()
    {
        m_quad.setFillColor(sf::Color::White);
    }


    void BasicButton::draw(MasterRenderer& renderer) noexcept
    {
        renderer.draw(m_quad);
        renderer.draw(m_text);
    }

    void BasicButton::setPosition(const sf::Vector2f& position)
    {
        m_quad.setPosition(position);

        m_text.setPosition(position);
        m_text.move(m_quad.getSize().x / 2 - m_text.getLocalBounds().width  / 2,
                    m_quad.getSize().y / 2 - m_text.getLocalBounds().height / 2);
    }

    const sf::Vector2f BasicButton::getSize() const
    {
        return m_quad.getSize();
    }
}
