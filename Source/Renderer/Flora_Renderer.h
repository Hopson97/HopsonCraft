#ifndef FLORA_RENDERER_H
#define FLORA_RENDERER_H

#include <vector>

#include "../World/Chunk/Chunk_Location.h"

#include "../Shaders/Flora_Shader.h"

class Chunk;
class Camera;

class Flora_Renderer
{
    public:
        void addChunk   (const Chunk& chunk );

        void render     (const Camera& camera);

    private:
        void prepareChunk   (const Chunk& chunk);

        Shader::Flora_Shader m_shader;

        std::vector<const Chunk*> m_chunks;
};

#endif // FLORA_RENDERER_H
