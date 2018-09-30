#include "TimeCheck.h"

#include "../HUD/Debug.h"

FrameTimeChecker::FrameTimeChecker(const std::string& name, const std::string& abv)
:   m_name          (name)
,   m_abbreviation  (abv)
{

}

void FrameTimeChecker::update()
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

void FrameTimeChecker::registerForDebug(Debug_HUD& debugHUD)
{
    debugHUD.addDebugSector(m_name +            " Time: %.1fms",    &m_frameTime);
    debugHUD.addDebugSector(m_abbreviation  +   " %.1f",            &m_fps);
}
