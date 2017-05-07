#ifndef TIME_CHECK_H_INCLUDED
#define TIME_CHECK_H_INCLUDED

#include <SFML/System/Clock.hpp>

struct Frame_Time_Checker
{
    public:
        void         update();
        const float& getFrameTime();
        const float& getFPS();

    private:
        sf::Clock   m_timer;
        sf::Clock   m_updateTimer;
        float       m_frameCount = 0;
        float       m_frameTime  = 0;
        float       m_fps        = 0;
};

#endif // TIME_CHECK_H_INCLUDED
