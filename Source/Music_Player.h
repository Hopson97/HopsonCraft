#ifndef MUSIC_PLAYER_H_INCLUDED
#define MUSIC_PLAYER_H_INCLUDED

#include <SFML/Audio.hpp>

class Music_Player
{
    public:
        Music_Player();

        void update();

    private:
        sf::Music m_music;
        sf::Time  m_duration;
        sf::Clock m_timer;
};

#endif // MUSIC_PLAYER_H_INCLUDED
