#ifndef TIME_CHECK_H_INCLUDED
#define TIME_CHECK_H_INCLUDED

#include <SFML/System/Clock.hpp>

#include <string>

class Debug_HUD;

struct FrameTimeChecker
{
    public:
        FrameTimeChecker(const std::string& name, const std::string& abv);

        void         update();

        void registerForDebug(Debug_HUD& debugHUD);

    private:
        sf::Clock   m_timer;
        sf::Clock   m_updateTimer;
        float       m_frameCount = 0;
        float       m_frameTime  = 0;
        float       m_fps        = 0;

        std::string m_name,
                    m_abbreviation;
};

#endif // TIME_CHECK_H_INCLUDED
