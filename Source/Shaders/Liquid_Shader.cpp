#include "Liquid_Shader.h"

#include "../Maths/Matrix_Maths.h"

namespace Shader
{
    Liqud_Shader::Liqud_Shader()
    :   Simple_Shader   ("Liquid_Vertex", "Liquid_Fragment")
    {
        getUniformLocations();
    }

    void Liqud_Shader::loadWaveTimer(float time)
    {
        loadFloat(m_locationWaveTimer, time);
    }

    void Liqud_Shader::getUniformLocations()
    {
        Simple_Shader::getUniformLocations();

        m_locationWaveTimer = glGetUniformLocation(getID(), "waveTimer");
    }

}
