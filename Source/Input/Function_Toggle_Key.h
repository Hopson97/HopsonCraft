#ifndef FUNCTION_TOGGLE_KEY_H
#define FUNCTION_TOGGLE_KEY_H

#include <SFML/System/Clock.hpp>
#include <SFML/Window/Keyboard.hpp>

class Toggle
{
    public:
        Toggle(sf::Keyboard::Key key, sf::Time delay);

        explicit operator bool();

    private:
        void checkInput();

        sf::Keyboard::Key   m_toggleKey;

        bool        m_isToogleOn = false;
        sf::Time    m_toggleDelay;
        sf::Clock   m_toggleTimer;
};

class Toggle_Bool
{
    public:
        Toggle_Bool(sf::Keyboard::Key key, sf::Time delay, bool& value);

        void input();

    private:
        sf::Keyboard::Key   m_toggleKey;

        bool*       m_pValue        = nullptr;
        sf::Time    m_toggleDelay;
        sf::Clock   m_toggleTimer;
};

#endif // FUNCTION_TOGGLE_KEY_H
