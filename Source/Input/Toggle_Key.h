#ifndef TOGGLE_KEY_H
#define TOGGLE_KEY_H

#include <functional>
#include <SFML/Graphics.hpp>

struct Toggle_Key
{
    Toggle_Key( std::function<void(void)> f, sf::Keyboard::Key k, float seconds );

    bool checkInput();

    private:
        std::function<void(void)>   m_func;
        sf::Keyboard::Key           m_key;
        float                       m_toggleTime;
        sf::Clock                   m_toggleClock;
};

#endif // TOGGLE_KEY_H
