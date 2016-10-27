#ifndef DEBUG_DISPLAY_H
#define DEBUG_DISPLAY_H

#include <string>

namespace Debug_Display
{
    void init       ();
    void addFPS     (float fps);
    void addText    (const std::string& text);
    void draw       ();
}

#endif // DEBUG_DISPLAY_H
