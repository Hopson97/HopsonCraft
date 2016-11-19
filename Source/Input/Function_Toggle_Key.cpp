#include "function_toggle_key.h"

Function_Toggle_Key::Function_Toggle_Key (std::function<void(void)> func, sf::Keyboard::Key key, float seconds)
:   m_func          (func)
,   m_key           (key)
,   m_toggleTime    (seconds)
{ }

bool Function_Toggle_Key::checkInput(const sf::Event& e)
{
    if (e.type == sf::Event::KeyPressed &&
        m_toggleClock.getElapsedTime().asSeconds() > m_toggleTime)
    {
        if (e.key.code == m_key)
            m_func();
                m_toggleClock.restart();
            return true;
    }
    return false;
}
