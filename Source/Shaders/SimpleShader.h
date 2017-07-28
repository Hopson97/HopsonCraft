#ifndef SimpleShader_H_INCLUDED
#define SimpleShader_H_INCLUDED

#include "ShaderProgram.h"

class SimpleShader : public ShaderProgram
{
    public:
        SimpleShader();
        SimpleShader(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);
        virtual ~SimpleShader() = default;

        void setProjViewMatrix  (const Matrix4& matrix);
        void setModelMatrix     (const Matrix4& matrix);

    protected:
        virtual void getUniformLocations() override;

        GLuint m_locationProjViewMatrix = 0;
        GLuint m_locationModelMatrix    = 0;
};

#endif // SimpleShader_H_INCLUDED
