#ifndef CHUNK_RENDERER_H
#define CHUNK_RENDERER_H

#include "Chunk_Shader.h"

#include <vector>

#include "Chunk/Chunk_Location.h"

class Chunk;
class Camera;

class Chunk_Renderer
{
    public:
        void addChunk   (const Chunk& chunk );

        void render     (const Camera& camera);

    private:
        void prepareChunk   (const Chunk& chunk);

        Shader::Ground_Chunk_Shader m_shader;

        std::vector<const Chunk*> m_chunks;
};

#endif // CHUNK_RENDERER_H
