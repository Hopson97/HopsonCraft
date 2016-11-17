#ifndef CHUNK_RENDERER_H
#define CHUNK_RENDERER_H

#include <vector>

#include "../World/Chunk/Chunk_Location.h"

#include "Solid_Block_Shader.h"

class Chunk;
class Camera;

class Solid_Block_Renderer
{
    public:
        void addChunk   (const Chunk& chunk );

        void render     (const Camera& camera);

    private:
        void prepareChunk   (const Chunk& chunk);

        Shader::Solid_Block_Shader m_shader;

        std::vector<const Chunk*> m_chunks;
};

#endif // CHUNK_RENDERER_H
