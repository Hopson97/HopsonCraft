#ifndef FONT_MANAGER_H_INCLUDED
#define FONT_MANAGER_H_INCLUDED

#include <SFML/Graphics.hpp>

#include "Resource_Manager.h"

enum class Font_ID
{
    RS
};

class Font_Manager : public Resource_Manager<sf::Font, Font_ID>
{
    public:
        Font_Manager();
};


#endif // FONT_MANAGER_H_INCLUDED
