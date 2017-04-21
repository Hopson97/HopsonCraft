#include "Toggle_Option_Button.h"

#include "../Display.h"
#include "../Renderer/RMaster.h"

namespace GUI
{
    Toggle_Option_Button::Toggle_Option_Button(std::string&& title,
                                               std::vector<std::string>&& order,
                                               std::vector<int32_t>&&     values,
                                               int32_t& option)
    :   m_options       (std::move(order))
    ,   m_optionValues  (std::move(values))
    ,   mp_option       (&option)
    ,   m_label         (std::move(title))
    {
        m_quad.setSize({800, 150});
        m_quad.setTexture(&Component::guiTexture);
        m_quad.setOutlineColor(sf::Color::Black);
        m_quad.setOutlineThickness(4);

        nextOption();
    }

    void Toggle_Option_Button::input(const sf::Event& e)
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
            nextOption();
        }
    }

    void Toggle_Option_Button::nextOption()
    {
        m_optionIndex++;
        if (m_optionIndex > (int32_t)m_options.size() - 1 )
        {
            m_optionIndex = 0;
        }
        initText(m_text, 40, m_label + ": " + m_options[m_optionIndex]);
        *mp_option = m_optionValues[m_optionIndex];
    }


    void Toggle_Option_Button::update()
    { }

    void Toggle_Option_Button::draw(Renderer::Master& renderer)
    {
        renderer.draw(m_quad);
        renderer.draw(m_text);
    }

    void Toggle_Option_Button::setPosition(const sf::Vector2f& position)
    {
        m_quad.setPosition(position);

        m_text.setPosition(position);
        m_text.move(m_quad.getSize().x / 2 - m_text.getLocalBounds().width  / 2,
                    m_quad.getSize().y / 2 - m_text.getLocalBounds().height / 2);
    }

    const sf::Vector2f Toggle_Option_Button::getSize() const
    {
        return m_quad.getSize();
    }


}
