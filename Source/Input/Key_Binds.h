#ifndef KEY_BINDS_H_INCLUDED
#define KEY_BINDS_H_INCLUDED

#include <map>
#include <SFML/Graphics.hpp>

namespace Key_Binds
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
    sf::Keyboard::Key                       getKey  (Control control);
}

#endif // KEY_BINDS_H_INCLUDED
