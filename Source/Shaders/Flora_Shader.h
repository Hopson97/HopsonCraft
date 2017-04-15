#ifndef LIQUID_SAHDER_H_INCLUDED
#define LIQUID_SAHDER_H_INCLUDED

#include "Simple_Shader.h"

namespace Shader
{
    class Flora_Shader : public Simple_Shader
    {
        public:
            Flora_Shader();

            void loadWindTimer(float time);

            void getUniformLocations() override;

        private:
            GLuint m_locationWindTime;
    };
}

#endif // LIQUID_SAHDER_H_INCLUDED
