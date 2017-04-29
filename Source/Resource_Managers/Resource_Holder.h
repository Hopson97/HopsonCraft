#ifndef RESOURCE_HOLDER_H_INCLUDED
#define RESOURCE_HOLDER_H_INCLUDED

#include "Texture_Manager.h"
#include "Sound_Manager.h"
#include "Font_Manager.h"

struct Resource_Holder
{
    Resource_Holder()
    :   textures        ("Data/Textures/",  ".png")
    ,   fonts           ("Data/Fonts/",     ".ttf")
    ,   soundBuffers    ("Data/Sounds/",    ".ogg")
    {}

    ResourceManager<sf::Texture>       textures;
    ResourceManager<sf::Font>          fonts;
    ResourceManager<sf::SoundBuffer>   soundBuffers;
};

Resource_Holder& getResources();

#endif // RESOURCE_HOLDER_H_INCLUDED
