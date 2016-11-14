#include "Shader.h"

#include "Shader_Loader.h"

#include <stdexcept>
#include <iostream>

namespace Shader
{
    Shader_Program::Shader_Program(const std::string& vertexShaderFile, const std::string& fragmentShaderFile)
    {
        create(vertexShaderFile, fragmentShaderFile);
    }

    Shader_Program::~Shader_Program()
    {
        glDeleteProgram (m_shaderProgram);
        m_shaderProgram = 0;
    }

    void Shader_Program::create(const std::string& vertexShaderFile, const std::string& fragmentShaderFile)
    {
        m_shaderProgram = Shader::load(vertexShaderFile, fragmentShaderFile);
    }

    void Shader_Program::useProgram() const
    {
        glUseProgram (m_shaderProgram);
    }

    GLuint Shader_Program::getId() const
    {
        return m_shaderProgram;
    }


    void Shader_Program::loadMatrix4(GLuint location, const Matrix4& matrix) const
    {
        glUniformMatrix4fv (location, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void Shader_Program::loadVector3(GLuint location, const Vector3& vect) const
    {
        glUniform3fv (location, 1, glm::value_ptr(vect));
    }

    void Shader_Program::loadInteger(GLuint location, int data) const
    {
        glUniform1i (location, data);
    }

    void Shader_Program::loadFloat(GLuint location, float data) const
    {
        glUniform1f (location, data);
    }

    void Shader_Program::bindAttribute(GLuint location, const std::string& name)
    {
        glBindAttribLocation(m_shaderProgram, location, name.c_str());
    }
} //Namespace Shader
