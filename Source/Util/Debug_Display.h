#ifndef DEBUG_DISPLAY_H
#define DEBUG_DISPLAY_H

#include <GL/glew.h>
#include <string>

#include "../World/Block/Block_Type/Block_Type.h"

class Master_Renderer;

namespace Debug_Display
{
    void init               ();

    void addFPS             (float fps);

    void addHighestBlock    (uint32_t y);
    void addPlayerPosition  (const Vector3& location);
    void addPlayerLightLevel(const Vector3& location, const Chunk* chunk);
    void addLookVector      (const Vector3& rotation);

    void addChunkUpdates    (size_t numChunks);
    void addChunkAmounth    (size_t numChunks);

    void addheldBlock       (const Block::Block_Type& block);

    void draw               (Master_Renderer& renderer);
}

#endif // DEBUG_DISPLAY_H
