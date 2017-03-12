#include "Music_Player.h"

Music_Player::Music_Player()
{
    m_music.openFromFile("Data/Music/rim.ogg");
    m_music.play();
}

void Music_Player::update()
{
    if (m_music.getPlayingOffset() >= m_music.getDuration() + sf::seconds(1))
    {
        m_music.openFromFile("Data/Music/rim.ogg");
        m_music.play();
    }
}
