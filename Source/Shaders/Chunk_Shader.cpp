#include "Chunk_Shader.h"

#include "../World/World_Constants.h"

namespace Shader
{
    Chunk_Shader::Chunk_Shader(std::string&& vertexShaderFile)
    :   Simple_Shader   (std::move(vertexShaderFile), "Block")
    {
        getUniformLocations();
        bind();
        Shader::Shader_Program::loadInt(m_locationMaxLightValue, MAX_LIGHT);
        unbind();
    }

    void Chunk_Shader::loadTimer(float time)
    {
        loadFloat(m_locationTimer, time);
    }

    void Chunk_Shader::getUniformLocations()
    {
        Simple_Shader::getUniformLocations();

        m_locationTimer         = glGetUniformLocation(getID(), "timer");
        m_locationMaxLightValue = glGetUniformLocation(getID(), "maxLightValue");
    }
}
