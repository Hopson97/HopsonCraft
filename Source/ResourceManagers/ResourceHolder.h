#ifndef ResourceHolder_H_INCLUDED
#define ResourceHolder_H_INCLUDED

#include "ResourceManager.h"

struct ResourceHolder
{
    ResourceHolder()
    :   textures        ("Data/Textures/",  ".png")
    ,   fonts           ("Data/Fonts/",     ".ttf")
    ,   soundBuffers    ("Data/Sounds/",    ".ogg")
    {}

    ResourceManager<sf::Texture>       textures;
    ResourceManager<sf::Font>          fonts;
    ResourceManager<sf::SoundBuffer>   soundBuffers;
};

ResourceHolder& getResources();

#endif // ResourceHolder_H_INCLUDED
