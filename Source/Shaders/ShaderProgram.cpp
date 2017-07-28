#include "ShaderProgram.h"

#include "ShaderLoader.h"

ShaderProgram::ShaderProgram(const std::string& vertexShaderFile, const std::string& fragmentShaderFile)
:   m_programID (loadShader(vertexShaderFile, fragmentShaderFile))
{ }

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(m_programID);
}

void ShaderProgram::bind()
{
    glUseProgram(m_programID);
}

void ShaderProgram::unbind()
{
    glUseProgram(0);
}

void ShaderProgram::loadInt(GLuint location, int value)
{
    glUniform1i(location, value);
}

void ShaderProgram::loadFloat(GLuint location, float value)
{
    glUniform1f(location, value);
}

void ShaderProgram::loadVector2(GLuint location, const Vector2& vector)
{
    glUniform2f(location, vector.x, vector.y);
}

void ShaderProgram::loadMatrix4(GLuint location, const Matrix4& matrix)
{
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}


GLuint ShaderProgram::getID() const
{
    return m_programID;
}
