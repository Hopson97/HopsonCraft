#include "function_toggle_key.h"

Function_Toggle_Key::Function_Toggle_Key (std::function<void(void)> func, sf::Keyboard::Key key, sf::Time seconds)
:   m_func          (func)
,   m_key           (key)
,   m_toggleTime    (seconds)
{ }

bool Function_Toggle_Key::checkInput()
{
    if (sf::Keyboard::isKeyPressed(m_key) && m_toggleClock.getElapsedTime().asSeconds() > m_toggleTime.asSeconds())
    {
        m_func();
        m_toggleClock.restart();
        return true;
    }
    return false;
}
