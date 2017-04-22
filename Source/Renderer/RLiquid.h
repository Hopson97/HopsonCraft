#ifndef RLIQUID_H_INCLUDED
#define RLIQUID_H_INCLUDED

#include <vector>
#include <SFML/System/Clock.hpp>

#include "../Shaders/Liquid_Shader.h"
#include "RInfo.h"

struct Camera;

namespace Chunk
{
    class Section;
}

namespace Renderer
{
    class RLiquid
    {
        public:
            void draw (const Chunk::Section& section);

            void update(const Camera& camera);

        private:
            std::vector<Info> m_renderInfo;

            Shader::Liquid_Shader m_shader;

            sf::Clock m_waveTimer;
    };
}

#endif // RLIQUID_H_INCLUDED
