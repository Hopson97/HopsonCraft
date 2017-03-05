#ifndef TEXTURE_MANAGER_H_INCLUDED
#define TEXTURE_MANAGER_H_INCLUDED

#include <SFML/Graphics.hpp>

#include "Resource_Manager.h"


enum class Texture_ID
{
    Vignette
};

class Texture_Manager : public Resource_Manager<sf::Texture, Texture_ID>
{
    public:
        Texture_Manager();
};

#endif // TEXTURE_MANAGER_H_INCLUDED
