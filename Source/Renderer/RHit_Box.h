#ifndef RHIT_BOX_H_INCLUDED
#define RHIT_BOX_H_INCLUDED

#include <vector>
#include <SFML/System/Clock.hpp>

#include "../Shaders/Simple_Shader.h"
#include "../Model.h"

struct Camera;

namespace Renderer
{
    class RHit_Box
    {
        public:
            RHit_Box();

            void draw   (const Vector3& location);
            void update (const Camera& camera);

        private:
            Vector3 m_nextDrawLocation;

            Shader::Simple_Shader m_shader;

            Model m_cubeModel;
    };
}

#endif // RHIT_BOX_H_INCLUDED
