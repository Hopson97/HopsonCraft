#include "Flora_Shader.h"

#include "Matrix_Maths.h"

namespace Shader
{
    Flora_Shader::Flora_Shader()
    :   Shader_Program ("Flora_Vertex", "Flora_Fragment")
    {
        bindAttributes();
        getUniformLocations();

        useProgram();
        loadMatrix4(m_locationProjectionMatrix, Maths::createPerspectiveMatrix());
        glUseProgram(0);
    }

    void Flora_Shader::loadCameraMatrix(const Camera& camera)
    {
        loadMatrix4(m_locationViewMatrix, Maths::createViewMatrix(camera));
    }

    void Flora_Shader::loadChunkMatrix(const Matrix4& matrix)
    {
        loadMatrix4(m_locationModelMatrix, matrix);
    }


    void Flora_Shader::loadSkyColour (const Vector3& skyColour )
    {
        loadVector3 ( m_skyColourLocation, skyColour );
    }

    void Flora_Shader::bindAttributes()
    {
        bindAttribute(0, "inVertexCoords");
        bindAttribute(1, "inTextureCoords");
    }

    void Flora_Shader::getUniformLocations()
    {
        m_locationViewMatrix        = glGetUniformLocation ( getId(), "viewMatrix"          );
        m_locationModelMatrix       = glGetUniformLocation ( getId(), "modelMatrix"         );
        m_locationProjectionMatrix  = glGetUniformLocation ( getId(), "projectionMatrix"    );
    }
}
