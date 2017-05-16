#include "Function_Toggle_Key.h"

Toggle::Toggle(sf::Keyboard::Key key, sf::Time delay)
:   m_toggleKey     (key)
,   m_toggleDelay   (delay)
{ }

Toggle::operator bool()
{
    checkInput();
    return m_isToogleOn;
}

void Toggle::checkInput()
{
    if (m_toggleDelay.asMilliseconds() <
        m_toggleTimer.getElapsedTime().asMilliseconds())
    {
        if (sf::Keyboard::isKeyPressed(m_toggleKey))
        {
            m_isToogleOn = !m_isToogleOn;
            m_toggleTimer.restart();
        }
    }
}

Toggle_Bool::Toggle_Bool(sf::Keyboard::Key key, sf::Time delay, bool& value)
:   m_toggleKey     (key)
,   m_pValue        (&value)
,   m_toggleDelay   (delay)
{ }

void Toggle_Bool::input()
{
    if (m_toggleDelay.asMilliseconds() <
        m_toggleTimer.getElapsedTime().asMilliseconds())
    {
        if (sf::Keyboard::isKeyPressed(m_toggleKey))
        {
            *m_pValue = !*m_pValue;
            m_toggleTimer.restart();
        }
    }
}

