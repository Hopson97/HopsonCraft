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
        struct Info
        {
            Info(GLuint vaoID, GLuint indices)
            :   vao         (vaoID)
            ,   indexCount  (indices) {}

            GLuint vao;
            GLuint indexCount;
        };

        public:
            void draw (const Chunk::Section& section);

            void update(const Camera& camera);

        private:
            void prepare(const Info& section);

        private:
            std::vector<Info> m_renderInfo;

            Shader::Solid_Shader m_shader;
    };
}

#endif // RCHUNK_H_INCLUDED
