#ifndef SIMPLE_SHADER_H_INCLUDED
#define SIMPLE_SHADER_H_INCLUDED

#include "ShaderProgram.h"

namespace Shader
{
    class Simple_Shader : public Shader_Program
    {
        public:
            Simple_Shader();
            Simple_Shader(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);
            virtual ~Simple_Shader() = default;

            void setProjViewMatrix  (const Matrix4& matrix);
            void setModelMatrix     (const Matrix4& matrix);

        protected:
            virtual void getUniformLocations() override;

            GLuint m_locationProjViewMatrix = 0;
            GLuint m_locationModelMatrix    = 0;
    };
}

#endif // SIMPLE_SHADER_H_INCLUDED
