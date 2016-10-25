#include "Frames_Per_Second_Checker.h"


#include <string>
#include <iostream>

void Frames_Per_Second_Checker :: update ()
{
    m_frameTimes    += getFPS();
    m_frameCounter  ++;

    if ( m_printTimer.getElapsedTime().asSeconds() >= 1.3 )
    {
        float framesPerSecond = m_frameTimes / m_frameCounter;
        print ( framesPerSecond );

        reset();
    }
}

float Frames_Per_Second_Checker :: getFPS ()
{
    return (1000000.0f / m_clock.restart().asMicroseconds());
}

void Frames_Per_Second_Checker :: print ( float framesPerSecond )
{
    std::cout << framesPerSecond << std::endl;
}

void Frames_Per_Second_Checker :: reset ()
{
    m_frameTimes    = 0;
    m_frameCounter  = 0;

    m_printTimer.restart();
}
