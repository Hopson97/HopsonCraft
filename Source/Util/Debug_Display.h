#ifndef DEBUG_DISPLAY_H
#define DEBUG_DISPLAY_H

#include <string>

#include "OpenGL/GLM/glm_transformations.h"
#include "Block.h"

namespace Debug_Display
{
    void init               ();

    void addFPS             (float fps);

    void addPlayerPosition  (const Vector3& location);
    void addLookVector      (const Vector3& rotation);

    void addChunkUpdates    (size_t numChunks);
    void addChunkAmounth    (size_t numChunks);

    void addheldBlock       (const Block_t& block);

    void draw               ();
}

#endif // DEBUG_DISPLAY_H
