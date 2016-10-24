#ifndef CHUNK_SOLID_RENDERER_H
#define CHUNK_SOLID_RENDERER_H

#include <vector>

#include "Chunk_Shader.h"

class Chunk;
class Camera;

class Chunk_Ground_Renderer
{
    public:
        Chunk_Ground_Renderer();

        void processChunk   (const Chunk& chunk);
        void render         (const Camera& camera);

    private:
        void prepareChunk   (const Chunk& chunk);

    private:
        Shader::Ground_Chunk_Shader m_shader;
        std::vector<const Chunk*>   m_chunks;
};

#endif // CHUNK_SOLID_RENDERER_H
