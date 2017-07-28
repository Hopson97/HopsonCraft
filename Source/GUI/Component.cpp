#include "Component.h"

#include "../Display.h"
#include "../ResourceManagers/ResourceHolder.h"

namespace GUI
{
    Component::Component()
    {

    }

    bool Component::touchingMouse(const sf::Shape& sprite) const
    {
        return  sprite.getGlobalBounds().contains
                (
                    sf::Mouse::getPosition(Display::get().getRaw()).x,
                    sf::Mouse::getPosition(Display::get().getRaw()).y
                );
    }

    bool Component::clicked (const sf::Shape& sprite, const sf::Event& e) const
    {
        if(touchingMouse(sprite))
        {
            if (e.type == sf::Event::MouseButtonPressed)
                return (e.mouseButton.button == sf::Mouse::Left);
        }
        return false;

    }

    void Component::initText(sf::Text& text, int size, const std::string& title)
    {
        text.setFont(ResourceHolder::getFont("rs"));
        text.setString(title);
        text.setOutlineColor(sf::Color::Black);
        text.setOutlineThickness(2);
        text.setCharacterSize(size);
    }

    sf::Text Component::initText (int size, const std::string& title)
    {
        sf::Text t;
        initText(t, size, title);
        return t;
    }


}


