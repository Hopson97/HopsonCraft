#ifndef CHUNK_RENDERER_H
#define CHUNK_RENDERER_H

#include <vector>
#include "Chunk_Shader.h"

class Chunk;
class Camera;

class Chunk_Renderer
{
    public:
        Chunk_Renderer(const Shader::Chunk_Shader& shader);

        void addChunk   (const Chunk& chunk);
        void render     (const Camera& camera);

    protected:
        virtual void prepareRender() = 0;
        virtual void prepareChunk (const Chunk& chunk) = 0;

    private:
        Shader::Chunk_Shader m_shader;

        std::vector<const Chunk*> m_chunks;
};

#endif // CHUNK_RENDERER_H
