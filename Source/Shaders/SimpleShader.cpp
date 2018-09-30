#include "SimpleShader.h"

#include "../Maths/Matrix.h"

SimpleShader::SimpleShader()
:   ShaderProgram ("Simple", "Simple")
{
    getUniformLocations();
}

SimpleShader::SimpleShader(const std::string& vertexShaderFile, const std::string& fragmentShaderFile)
:   ShaderProgram (vertexShaderFile, fragmentShaderFile)
{

}

void SimpleShader::setProjViewMatrix(const Matrix4& matrix)
{
    loadMatrix4(m_locationProjViewMatrix, matrix);
}

void SimpleShader::setModelMatrix(const Matrix4& matrix)
{
    loadMatrix4(m_locationModelMatrix, matrix);
}

void SimpleShader::getUniformLocations()
{
    m_locationProjViewMatrix    = glGetUniformLocation(getID(), "projViewMatrix");
    m_locationModelMatrix       = glGetUniformLocation(getID(), "modelMatrix");
}
