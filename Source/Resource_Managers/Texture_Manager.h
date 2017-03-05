#ifndef TEXTURE_MANAGER_H_INCLUDED
#define TEXTURE_MANAGER_H_INCLUDED

#include <SFML/Graphics.hpp>

#include "Resource_Manager.h"


enum class Texture_ID
{
    Splash_SFML,
    Splash_MH,

    Player_Legs,

    Player_Body_Shirt,
    Player_Head_None,
    Player_Shield_Wood,
    Player_Sword_Wood,
    Player_Wood_Slash,

    Entity_Blacksmith,
    Entity_Slime,
    Entity_Bee,

    Entity_Coral_Slime,

    Zone_Village,
    Zone_Forest,
    Zone_Beach,
    Zone_Mountians,
    Zone_River,
    Zone_Desert,

    Proj_Stinger,

    GUI_Exit_Button,

    World_Map,

    Hearts,
};

class Texture_Manager : public Resource_Manager<sf::Texture, Texture_ID>
{
    public:
        Texture_Manager();
};

#endif // TEXTURE_MANAGER_H_INCLUDED
