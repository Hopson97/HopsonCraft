#ifndef FUNCTION_TOGGLE_KEY_H
#define FUNCTION_TOGGLE_KEY_H

#include <SFML/System/Clock.hpp>
#include <SFML/Window/Keyboard.hpp>

class Toggle
{
    public:
        Toggle(sf::Keyboard::Key key, sf::Time delay);

        explicit operator bool()
        {
            checkInput();
            return m_isToogleOn;
        }

    private:
        void checkInput();

        sf::Keyboard::Key   m_toggleKey;

        bool        m_isToogleOn = false;
        sf::Time    m_toggleDelay;
        sf::Clock   m_toggleTimer;
};

#endif // FUNCTION_TOGGLE_KEY_H
