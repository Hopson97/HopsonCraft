#ifndef LIQUID_SAHDER_H_INCLUDED
#define LIQUID_SAHDER_H_INCLUDED

#include "Simple_Shader.h"

namespace Shader
{
    class Liquid_Shader : public Simple_Shader
    {
        public:
            Liquid_Shader();

            void loadWaveTimer(float time);

            void getUniformLocations() override;

        private:
            GLuint m_locationWaveTimer;
    };
}

#endif // LIQUID_SAHDER_H_INCLUDED
