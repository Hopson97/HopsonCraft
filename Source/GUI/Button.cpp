#include "Button.h"

namespace GUI
{
    Button::Button(const sf::RectangleShape& rect)
    :   m_rShape    (rect)
    { }

    void Button::input(const sf::Event& e)
    {
        if (touchingMouse(m_rShape))
        {
            onMouseTouch();
        }
        else
        {
            onNoInteract();
        }

        if(clicked(m_rShape, e))
        {
            onClick();
        }
    }
}
