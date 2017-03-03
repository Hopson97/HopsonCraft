#ifndef SIMPLE_SHADER_H_INCLUDED
#define SIMPLE_SHADER_H_INCLUDED

#include "Shader_Program.h"

namespace Shader
{
    class Simple_Shader : public Shader_Program
    {
        public:
            Simple_Shader();

            void setViewMatrix  (const Matrix4& matrix);
            void setModelMatrix (const Matrix4& matrix);
            void setProjMatrix  (const Matrix4& matrix);

        private:
            void getUniformLocations() override;

            GLuint m_locationViewMatrix     = 0;
            GLuint m_locationModelMatrix    = 0;
            GLuint m_locationProjMatrix     = 0;
    };
}

#endif // SIMPLE_SHADER_H_INCLUDED
