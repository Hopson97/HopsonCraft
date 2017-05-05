#include "Music_Player.h"

#include <iostream>

#include "Util/File_Util.h"
#include "Util/Random.h"

Music_Player::Music_Player()
:   m_songs (getFileNamesFromFolder("Data/Music"))
,   m_currentSong   (Random::intInRange(0, m_songs.size() - 1))
{
    m_music.setVolume(1);
    getNextSong();
}

void Music_Player::update()
{
    if (m_duration <= m_timer.getElapsedTime())
    {
        uint32_t song;
        do
        {
            song = Random::intInRange(0, m_songs.size() - 1);
        } while (m_currentSong == song);

        m_currentSong = song;
        getNextSong();
    }
}

void Music_Player::getNextSong()
{
    auto& name      = m_songs[m_currentSong];
    auto fullName   = "Data/Music/" + name;

    m_music.openFromFile(fullName);
    m_music.stop();

    m_duration = m_music.getDuration() + sf::seconds(1);
    m_timer.restart();
    m_music.play();
}








