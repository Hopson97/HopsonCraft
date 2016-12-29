#include "Water_Shader.h"

#include "../Maths/Matrix_Maths.h"
#include "../Entity.h"

namespace Shader
{
    Water_Shader::Water_Shader()
    :   Chunk_Shader  ("Water_Vertex", "Water_Fragment")
    {
        getUniformLocations();
    }

    void Water_Shader::loadTime (float time) const
    {
        loadFloat(m_timeLocation, time);
    }

    void Water_Shader::bindAttributes()
    {
        Chunk_Shader::bindAttributes();
    }

    void Water_Shader::getUniformLocations()
    {
        m_timeLocation = glGetUniformLocation (getId(), "time");
    }
}
