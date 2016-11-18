#include "Flora_Shader.h"

#include "../Maths/Matrix_Maths.h"

namespace Shader
{
    Flora_Shader::Flora_Shader()
    :   Chunk_Shader ("Flora_Vertex", "Flora_Fragment")
    {
        getUniformLocations();
    }

    void Flora_Shader::loadTime(float time) const
    {
        Shader::Shader_Program::loadFloat(m_locationTime, time);
    }


    void Flora_Shader::bindAttributes()
    {}

    void Flora_Shader::getUniformLocations()
    {
        m_locationTime = glGetUniformLocation(getId(), "time");
    }
}
