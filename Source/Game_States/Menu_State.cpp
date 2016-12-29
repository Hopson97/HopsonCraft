#include "Menu_State.h"

#include <fstream>
#include <iostream>

#include "../Util/Display.h"
#include "../Application.h"
#include "Playing_State.h"

namespace State
{
    Main_Menu_State::Main_Menu_State(Application& application)
    :   Game_State  (application)
    {
        m_background.loadFromFile("Data/Images/bg.png");
        Display::showMouse();
    }

    void Main_Menu_State::input(const sf::Event& e)
    { }

    void Main_Menu_State::input()
    { }

    void Main_Menu_State::update(float dt, Camera& camera)
    {
        if (m_makeWorld)
        {
            m_application->changeState (std::make_unique<Playing_State>(
                                        *m_application,
                                        m_worldName,
                                        getSeed()));
        }
    }

    void Main_Menu_State::draw(float dt, Master_Renderer& renderer)
    { }

    void Main_Menu_State::exitState()
    { }

    uint32_t Main_Menu_State::getSeed()
    {
        std::string newString;
        for(auto& ch : m_seedString)
        {
            if (isalpha(ch))
            {
                int x = ch;
                newString += std::to_string(x);
            }
            else
            {
                newString += ch;
            }
        }

        while (newString.length() > 8) newString.pop_back();

        return std::stoi(newString);
    }
}
