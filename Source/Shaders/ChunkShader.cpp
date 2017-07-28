#include "ChunkShader.h"

#include "../World/WorldConstants.h"

ChunkShader::ChunkShader(std::string&& vertexShaderFile)
:   SimpleShader   (std::move(vertexShaderFile), "Block")
{
    getUniformLocations();
    bind();
    ShaderProgram::loadInt(m_locationMaxLightValue, MAX_LIGHT);
    unbind();
}

void ChunkShader::loadTimer(float time)
{
    loadFloat(m_locationTimer, time);
}

void ChunkShader::getUniformLocations()
{
    SimpleShader::getUniformLocations();

    m_locationTimer         = glGetUniformLocation(getID(), "timer");
    m_locationMaxLightValue = glGetUniformLocation(getID(), "maxLightValue");
}
