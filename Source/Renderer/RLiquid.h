#ifndef RLIQUID_H_INCLUDED
#define RLIQUID_H_INCLUDED

#include <vector>

#include <SFML/System/Clock.hpp>

#include "../Shaders/Liquid_Shader.h"

class Chunklet;
struct Camera;

namespace Renderer
{
    class RLiquid
    {
        public:
            void draw (const Chunklet& quad);

            void update(const Matrix4& viewMatrix);

        private:
            void prepare(const Chunklet& quad);

        private:
            std::vector<const Chunklet*> m_chunks;

            Shader::Liqud_Shader m_shader;

            sf::Clock m_wavesTimer;
    };
}

#endif // RLIQUID_H_INCLUDED
