#include "Toggle_Key.h"

Toggle_Key :: Toggle_Key ( std::function<void(void)> func, sf::Keyboard::Key key, float seconds )
:   m_func          ( func )
,   m_key           ( key )
,   m_toggleTime    ( seconds )
{ }

bool Toggle_Key :: checkInput()
{
    if ( sf::Keyboard::isKeyPressed( m_key ) &&
         m_toggleClock.getElapsedTime().asSeconds() >= m_toggleTime )
    {
        m_func();
        m_toggleClock.restart();
        return true;
    }
    return false;
}
