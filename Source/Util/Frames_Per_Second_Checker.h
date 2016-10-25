#ifndef FRAMES_PER_SECOND_CHECKER_H
#define FRAMES_PER_SECOND_CHECKER_H

#include <SFML/Graphics.hpp>

class Frames_Per_Second_Checker
{
    public:
        Frames_Per_Second_Checker() = default;

        void update     ();

    private:
        float getFPS();

        void print ( float framesPerSecond );

        void reset  ();

        sf::Clock   m_clock;
        sf::Clock   m_printTimer;
        int         m_frameCounter = 0;
        float       m_frameTimes  = 0;
};
#endif // FRAMES_PER_SECOND_CHECKER_H
