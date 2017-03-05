#ifndef SOUND_MANAGER_H_INCLUDED
#define SOUND_MANAGER_H_INCLUDED

#include <SFML/Audio.hpp>

#include "Resource_Manager.h"

enum class Sound_ID
{
    Splash_Made_By,

    Sword1,

    Dmg_Player,
    Dmg_Slime,
    Dmg_Bee
};

class Sound_Manager : public Resource_Manager<sf::SoundBuffer, Sound_ID>
{
    public:
        Sound_Manager();
        ~Sound_Manager();
};

#endif // SOUND_MANAGER_H_INCLUDED
