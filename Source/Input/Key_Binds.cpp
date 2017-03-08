#include "Key_Binds.h"

namespace Key_Binds
{
    std::map<Control, sf::Keyboard::Key> keys;

    void initKeys()
    {
        keys[Control::Player_Forwards]  = sf::Keyboard::W;
        keys[Control::Player_Back]      = sf::Keyboard::S;
        keys[Control::Player_Left]      = sf::Keyboard::A;
        keys[Control::Player_Right]     = sf::Keyboard::D;
        keys[Control::Player_Up]        = sf::Keyboard::Space;
        keys[Control::Player_Down]      = sf::Keyboard::LShift;
    }

    std::map<Control, sf::Keyboard::Key>& get()
    {
        static bool hasInit = false;
        if (!hasInit)
        {
            initKeys();
        }

        return keys;
    }

    sf::Keyboard::Key getKey(Control control)
    {
        static bool hasInit = false;
        if (!hasInit)
        {
            initKeys();
        }

        return keys[control];
    }
}
