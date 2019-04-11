#ifndef RCHUNK_H_INCLUDED
#define RCHUNK_H_INCLUDED

#include <vector>

#include <SFML/System.hpp>

#include "../Shaders/Chunk_Shader.h"
#include "RInfo.h"

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
            RChunk();

            void draw (const Chunk::Section& section);

            void update(const Camera& camera);

        private:
            void prepare(const Info& section);

        private:
            std::vector<Info> m_renderInfo;

            Shader::Chunk_Shader m_shader;

            sf::Clock m_timer;
    };
}

#endif // RCHUNK_H_INCLUDED
