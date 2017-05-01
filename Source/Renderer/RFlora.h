#ifndef RFlora_INCLUDED
#define RFlora_INCLUDED

#include <vector>
#include <SFML/System/Clock.hpp>

#include "../Shaders/Chunk_Shader.h"
#include "RInfo.h"

struct Camera;

namespace Chunk
{
    class Section;
}

namespace Renderer
{
    class RFlora
    {
        public:
            RFlora();

            void draw (const Chunk::Section& section);

            void update(const Camera& camera);

        private:
            std::vector<Info> m_renderInfo;

            Shader::Chunk_Shader m_shader;

            sf::Clock m_windTimer;
    };
}

#endif // RCHUNK_H_INCLUDED
