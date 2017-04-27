#ifndef MUSIC_PLAYER_H_INCLUDED
#define MUSIC_PLAYER_H_INCLUDED

#include <SFML/Audio.hpp>

class Music_Player
{
    public:
        Music_Player();

        void update();

    private:
        void getNextSong();

        sf::Music m_music;
        sf::Time  m_duration;
        sf::Clock m_timer;

        std::vector<std::string> m_songs;
        uint32_t m_currentSong = 0;
};

#endif // MUSIC_PLAYER_H_INCLUDED
