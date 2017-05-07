#include "Time_Check.h"

void Frame_Time_Checker::update()
{
    m_frameCount++;

    if (m_updateTimer.getElapsedTime().asSeconds() >= 0.3)
    {
        m_fps = m_frameCount / m_timer.getElapsedTime().asMilliseconds();
        if (m_fps > 0)
        {
            m_frameTime = 1.0f / m_fps;
        }
        m_fps *= 1000;
        m_frameCount = 0;
        m_updateTimer.restart();
        m_timer.restart();
    }
}

const float& Frame_Time_Checker::getFrameTime()
{
    return m_frameTime;
}

const float& Frame_Time_Checker::getFPS()
{
    return m_fps;
}
