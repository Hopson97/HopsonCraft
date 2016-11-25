#include "Dropdown.h"

#include "../Renderer/Master_Renderer.h"

namespace GUI
{
    Dropdown::Dropdown(int& optionPtr,
                       const std::string& label,
                       const std::vector<std::string>& options)
    :   m_optionPtr (optionPtr)
    {
        initText(m_label, 10, label);
    }

    void Dropdown::input(const sf::Event& e)
    {
        if (clicked(m_))
    }

    void Dropdown::update()
    {

    }

    void Dropdown::draw(Master_Renderer& renderer)
    {

    }

    void Dropdown::setPosition(const sf::Vector2f& position)
    {

    }

    const sf::Vector2f Dropdown::getSize() const
    {
        return {0, 0};
    }
}
