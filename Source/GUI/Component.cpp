#include "Component.h"

#include "../Util/Display.h"

namespace GUI
{
    sf::Texture GUI::Component::guiTexture;
    sf::Font    GUI::Component::guiFont;

    bool hasSetupResources;

    Component::Component()
    {
        if (!hasSetupResources)
        {
            guiTexture.loadFromFile("Data/Images/GUITexture.png");
            guiTexture.setRepeated(true);

            guiFont.loadFromFile("Data/Font/kongtext.ttf");    //monospace font
            hasSetupResources = true;
        }
    }

    bool Component::touchingMouse(const sf::Shape& sprite) const
    {
        return  sprite.getGlobalBounds().contains
                (
                    sf::Mouse::getPosition(Display::get()).x,
                    sf::Mouse::getPosition(Display::get()).y
                );
    }

}


