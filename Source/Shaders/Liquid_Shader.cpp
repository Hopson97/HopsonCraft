#include "Liquid_Shader.h"

#include "../Maths/Matrix_Maths.h"

namespace Shader
{
    Liquid_Shader::Liquid_Shader()
    :   Simple_Shader   ("Liquid", "Block")
    {
        getUniformLocations();
    }

    void Liquid_Shader::loadWaveTimer(float time)
    {
        loadFloat(m_locationWaveTimer, time);
    }

    void Liquid_Shader::getUniformLocations()
    {
        Simple_Shader::getUniformLocations();

        m_locationWaveTimer = glGetUniformLocation(getID(), "waveTimer");
    }

}
