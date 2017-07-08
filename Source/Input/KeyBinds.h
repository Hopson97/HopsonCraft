#ifndef KeyBinds_H_INCLUDED
#define KeyBinds_H_INCLUDED

#include <map>
#include <SFML/Graphics.hpp>

namespace KeyBinds
{
    enum class Control
    {
        Player_Forwards,
        Player_Back,
        Player_Left,
        Player_Right,
        Player_Up,
        Player_Down,
    };

    std::map<Control, sf::Keyboard::Key>&   get     ();
    sf::Keyboard::Key                       getKey  (Control control) noexcept;
}

#endif // KeyBinds_H_INCLUDED
