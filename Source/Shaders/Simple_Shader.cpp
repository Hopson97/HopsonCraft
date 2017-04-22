#include "Simple_Shader.h"

#include "../Maths/Matrix_Maths.h"

namespace Shader
{
    Simple_Shader::Simple_Shader()
    :   Shader_Program ("Simple", "Simple")
    {
        getUniformLocations();
    }

    Simple_Shader::Simple_Shader(const std::string& vertexShaderFile, const std::string& fragmentShaderFile)
    :   Shader_Program (vertexShaderFile, fragmentShaderFile)
    {

    }

    void Simple_Shader::setProjViewMatrix(const Matrix4& matrix)
    {
        loadMatrix4(m_locationProjViewMatrix, matrix);
    }

    void Simple_Shader::setModelMatrix(const Matrix4& matrix)
    {
        loadMatrix4(m_locationModelMatrix, matrix);
    }

    void Simple_Shader::getUniformLocations()
    {
        m_locationProjViewMatrix    = glGetUniformLocation(getID(), "projViewMatrix");
        m_locationModelMatrix       = glGetUniformLocation(getID(), "modelMatrix");
    }

}
