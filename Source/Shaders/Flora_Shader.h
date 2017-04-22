#ifndef FLORA_SHADER_H
#define FLORA_SHADER_H

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

#endif // FLORA_SHADER_H
