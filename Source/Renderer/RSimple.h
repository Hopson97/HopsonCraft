#ifndef SIMPLE_H_INCLUDED
#define SIMPLE_H_INCLUDED

#include <vector>
#include <SFML/System/Clock.hpp>

#include "../Shaders/Simple_Shader.h"
#include "../Model.h"

class Quad;
struct Camera;

namespace Renderer
{
    class RSimple
    {
        public:
            RSimple();

            void draw (const Quad& quad);
            void update(const Camera& camera);

        private:
            void prepare(const Quad& quad);

        private:
            std::vector<const Quad*> m_quads;

            Shader::Simple_Shader m_shader;

            Model m_cubeModel;
    };
}

#endif // SIMPLE_H_INCLUDED
