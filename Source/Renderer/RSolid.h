#ifndef RCHUNK_H_INCLUDED
#define RCHUNK_H_INCLUDED

#include <vector>

#include "../Shaders/Solid_Shader.h"

struct Camera;

namespace Chunk
{
    class Section;
}

namespace Renderer
{
    class RChunk
    {
        public:
            void draw (const Chunk::Section& section);

            void update(const Camera& camera);

        private:
            void prepare(const Chunk::Section& section);

        private:
            std::vector<const Chunk::Section*> m_chunks;

            Shader::Solid_Shader m_shader;
    };
}

#endif // RCHUNK_H_INCLUDED
