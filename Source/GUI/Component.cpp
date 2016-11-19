#include "Component.h"

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
        }
    }
}


