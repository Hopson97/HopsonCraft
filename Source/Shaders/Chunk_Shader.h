#ifndef CHUNK_SHADER_H_INCLUDED
#define CHUNK_SHADER_H_INCLUDED

#include "Simple_Shader.h"

namespace Shader
{
    class Chunk_Shader : public Simple_Shader
    {
        public:
            Chunk_Shader(std::string&& vertexShaderFile);

            void loadTimer(float time);

            void getUniformLocations() override;

        private:
            GLuint m_locationTimer;
            GLuint m_locationMaxLightValue;
    };
}

#endif // CHUNK_SHADER_H_INCLUDED
