#include "Dropdown.h"

#include "../Renderer/RMaster.h"

namespace GUI
{
    Dropdown::Dropdown(int& optionPtr,
                       const std::string& label,
                       const std::vector<std::string>& options)
    :   m_optionPtr (&optionPtr)
    {
        *m_optionPtr = 0;
        initText(m_label, 10, label);

        m_quad.setSize({70, 40});
        m_quad.setTexture(&Component::guiTexture);
        m_quad.setOutlineColor(sf::Color::Black);
        m_quad.setOutlineThickness(2);

        for (auto& option : options)
        {
            m_options.emplace_back(initText(15, option));
        }
    }

    void Dropdown::input(const sf::Event& e)
    {
        if (clicked(m_quad, e))
            m_isOpen = !m_isOpen;
    }

    void Dropdown::update()
    {

    }

    void Dropdown::draw(Renderer::Master& renderer)
    {
        if(m_isOpen);
    }

    void Dropdown::setPosition(const sf::Vector2f& position)
    {

    }

    const sf::Vector2f Dropdown::getSize() const
    {
        return {0, 0};
    }
}
