#include "Text_Box.h"

#include "../Display.h"
#include "../Renderer/RMaster.h"

namespace GUI
{
    Text_Box::Text_Box( unsigned maxTextLength,
                        const sf::Vector2f& size,
                        const std::string& labelText,
                        std::string& inputString)
    :   m_inputtedText  (&inputString)
    ,   m_maxLength     (maxTextLength)
    {
        m_quad.setSize(size);
        m_quad.setTexture(&Component::guiTexture);
        m_quad.setOutlineColor(sf::Color::Black);
        m_quad.setOutlineThickness(2);

        initText(m_text, 30, "");
        initText(m_label, 10, labelText);
    }

    void Text_Box::input(const sf::Event& e)
    {
        if (e.type == sf::Event::TextEntered)
        {
            if (m_isActive)
            {
                char code = e.text.unicode;
                if ((code >= 32 && code <= 126) &&
                    (code != 47) && //Back slash
                    (code != 92) && //Forward slash
                    m_inputtedText->length() <= m_maxLength)    //Lowercase
                {
                    *m_inputtedText += (static_cast<char>(e.text.unicode));
                }
                else if (code == 8 && m_inputtedText->length() >= 1)
                {
                    m_inputtedText->pop_back();
                }
            }
        }
        else if (e.type == sf::Event::MouseButtonPressed)
        {
            if (e.mouseButton.button == sf::Mouse::Left)
            {
                if (touchingMouse(m_quad))
                {
                    m_quad.setFillColor({200, 200, 200});
                    m_isActive = true;
                }
                else
                {
                    m_quad.setFillColor(sf::Color::White);
                    m_isActive = false;
                }
            }
        }
    }

    void Text_Box::update()
    {
        m_text.setString(*m_inputtedText);
    }

    void Text_Box::draw(Renderer::Master& renderer)
    {
        renderer.draw(m_quad);
        renderer.draw(m_text);
        renderer.draw(m_label);
    }

    void Text_Box::setPosition(const sf::Vector2f& position)
    {
        m_label.setPosition(position);

        m_quad.setPosition(position.x, position.y + 12);
        m_text.setPosition(position.x, position.y + 12);
        m_text.move(10, m_quad.getSize().y / 2 - m_text.getGlobalBounds().height / 2);
    }

    const sf::Vector2f Text_Box::getSize() const
    {
        return  {m_quad.getSize().x,
                m_quad.getSize().y + 15};
    }

}
