#ifndef DEBUG_DISPLAY_H
#define DEBUG_DISPLAY_H

#include <string>

#include "OpenGL/GLM/glm_transformations.h"

namespace Debug_Display
{
    void init               ();
    void addFPS             (float fps);
    void addPlayerPosition  (const Vector3 location);
    void draw               ();
}

#endif // DEBUG_DISPLAY_H
