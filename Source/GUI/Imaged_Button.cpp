#include "Imaged_Button.h"


#include "../Util/Display.h"
#include "../Renderer/Master_Renderer.h"
#include "../D_Settings.h"

namespace GUI
{
    Imaged_Button::Imaged_Button(const std::string& name, const std::string& text,
                                 std::function<void(void)>function)
    : m_function  (function)
    {
        m_quad.setSize({800, 150});
        m_quad.setTexture(&Component::guiTexture);
        m_quad.setOutlineColor(sf::Color::Black);
        m_quad.setOutlineThickness(2);

        m_text.setFont(Component::guiFont);
        m_text.setString(text);
        m_text.setOutlineColor(sf::Color::Black);
        m_text.setOutlineThickness(2);
        m_text.setCharacterSize(40);

        m_image.loadFromFile(name + ".png");
        m_imageRect.setSize({144, 144});
        m_imageRect.setTexture(&m_image);
        m_imageRect.setOutlineColor(sf::Color::Black);
        m_imageRect.setOutlineThickness(2);

    }

    void Imaged_Button::input(const sf::Event& e)
    {
        if (touchingMouse(m_quad))
        {
            m_quad.setFillColor({(sf::Uint8)Settings::SKY_RED   * (sf::Uint8)255,
                                 (sf::Uint8)Settings::SKY_GREEN * (sf::Uint8)255,
                                 (sf::Uint8)Settings::SKY_BLUE  * (sf::Uint8)255});

            if (e.type == sf::Event::MouseButtonPressed)
            {
                if (e.mouseButton.button == sf::Mouse::Left)
                {
                    m_function();
                }
            }
        }
        else
        {
            m_quad.setFillColor(sf::Color::White);
        }
    }

    void Imaged_Button::update()
    {

    }

    void Imaged_Button::draw(Master_Renderer& renderer)
    {
        renderer.draw(m_quad);
        renderer.draw(m_text);
        renderer.draw(m_imageRect);
    }

    void Imaged_Button::setPosition(const sf::Vector2f& position)
    {
        m_quad.setPosition(position);
        m_text.setPosition(position);
        m_imageRect.setPosition(position);

        m_text.move(m_imageRect.getSize().x + 5,
                    m_quad.getSize().y / 2 - m_text.getLocalBounds().height / 2);

        m_imageRect.move(3, 3);


    }

    const sf::Vector2f Imaged_Button::getSize() const
    {
        return m_quad.getSize();
    }
}
