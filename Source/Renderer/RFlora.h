#ifndef RFlora_INCLUDED
#define RFlora_INCLUDED

#include <vector>
#include <SFML/System/Clock.hpp>

#include "../Shaders/Flora_Shader.h"
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
            void draw (const Chunk::Section& section);

            void update(const Camera& camera);

        private:
            std::vector<Info> m_renderInfo;

            Shader::Flora_Shader m_shader;

            sf::Clock m_waveTimer;
    };
}

#endif // RCHUNK_H_INCLUDED
