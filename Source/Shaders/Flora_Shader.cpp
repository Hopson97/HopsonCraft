#include "Flora_Shader.h"

#include "../Maths/Matrix_Maths.h"

namespace Shader
{
    Flora_Shader::Flora_Shader()
    :   Simple_Shader   ("Flora", "Flora")
    {
        getUniformLocations();
    }

    void Flora_Shader::loadWindTimer(float time)
    {
        loadFloat(m_locationWindTime, time);
    }

    void Flora_Shader::getUniformLocations()
    {
        Simple_Shader::getUniformLocations();

        m_locationWindTime = glGetUniformLocation(getID(), "windTimer");
    }
}
