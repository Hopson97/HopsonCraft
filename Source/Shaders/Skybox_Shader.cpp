#include "Skybox_Shader.h"

#include "../Maths/Matrix_Maths.h"

namespace Shader
{
    Skybox_Shader::Skybox_Shader()
    :   Shader_Program  ("Sky_Box_Vertex", "Sky_Box_Fragment")
    {
        getUniformLocations();

        useProgram();
        loadMatrix4(m_locationProjectionMatrix, Maths::createPerspectiveMatrix());
        glUseProgram(0);
    }

    void Skybox_Shader::loadCameraMatrix(const Camera& camera) const
    {
        loadMatrix4(m_locationViewMatrix, Maths::createViewRotationMatrix(camera));
    }

    void Skybox_Shader::bindAttributes()
    { }

    void Skybox_Shader::getUniformLocations()
    {
        m_locationViewMatrix        = glGetUniformLocation (getId(), "viewMatrix");
        m_locationProjectionMatrix  = glGetUniformLocation (getId(), "projectionMatrix");
    }
}
