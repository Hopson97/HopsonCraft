#include "Water_Shader.h"

#include "Maths/Matrix_Maths.h"
#include "Camera.h"


namespace Shader
{
    Water_Shader::Water_Shader()
    :   Shader_Program  ("Water_Vertex", "Water_Fragment")
    {
        bindAttributes();
        getUniformLocations();

        useProgram();
        loadMatrix4(m_locationProjectionMatrix, Maths::createPerspectiveMatrix());
        glUseProgram(0);
    }

    void Water_Shader::loadCameraMatrix(const Camera& camera)
    {
        loadMatrix4(m_locationViewMatrix, Maths::createViewMatrix(camera));
    }

    void Water_Shader::loadChunkMatrix(const Matrix4& matrix)
    {
        loadMatrix4(m_locationModelMatrix, matrix);
    }

    void Water_Shader::loadSkyColour ( const Vector3& skyColour )
    {
        loadVector3 (m_skyColourLocation, skyColour);
    }

    void Water_Shader::loadTime (float time)
    {
        loadFloat(m_timeLocation, time);
    }

    void Water_Shader::bindAttributes()
    {
        bindAttribute(0, "inVertexCoords");
        bindAttribute(1, "inTextureCoords");
    }

    void Water_Shader::getUniformLocations()
    {
        m_locationViewMatrix        = glGetUniformLocation ( getId(), "viewMatrix"          );
        m_locationModelMatrix       = glGetUniformLocation ( getId(), "modelMatrix"         );
        m_locationProjectionMatrix  = glGetUniformLocation ( getId(), "projectionMatrix"    );

        m_timeLocation      = glGetUniformLocation ( getId(), "time" );
        m_skyColourLocation = glGetUniformLocation ( getId(), "skyColour" );
    }
}
