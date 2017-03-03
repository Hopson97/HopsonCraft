#ifndef RCHUNK_H_INCLUDED
#define RCHUNK_H_INCLUDED

#include <vector>

#include "../Shaders/Solid_Shader.h"

class Chunklet;
struct Camera;

namespace Renderer
{
    class RChunk
    {
        public:
            void draw (const Chunklet& quad);

            void update(const Camera& camera);

        private:
            void prepare(const Chunklet& quad);

        private:
            std::vector<const Chunklet*> m_chunks;

            Shader::Solid_Shader m_shader;
    };
}

#endif // RCHUNK_H_INCLUDED
