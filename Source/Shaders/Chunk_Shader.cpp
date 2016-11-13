#include "Chunk_Shader.h"

#include "../Maths/Matrix_Maths.h"
#include "../Player/Camera.h"

namespace Shader
{
    Ground_Chunk_Shader::Ground_Chunk_Shader()
    :   Shader_Program ("Ground_Vertex", "Ground_Fragment")
    {
        bindAttributes();
        getUniformLocations();

        useProgram();
        loadMatrix4(m_locationProjectionMatrix, Maths::createPerspectiveMatrix());
        glUseProgram(0);
    }



    void Ground_Chunk_Shader::loadCameraMatrix(const Camera& camera)
    {
        loadMatrix4(m_locationViewMatrix, Maths::createViewMatrix(camera));
    }

    void Ground_Chunk_Shader::loadChunkMatrix(const Matrix4& matrix)
    {
        loadMatrix4(m_locationModelMatrix, matrix);
    }


    void Ground_Chunk_Shader::loadSkyColour (const Vector3& skyColour )
    {
        loadVector3 ( m_skyColourLocation, skyColour );
    }

    void Ground_Chunk_Shader::bindAttributes()
    {
        bindAttribute(0, "inVertexCoords");
        bindAttribute(1, "inTextureCoords");
    }

    void Ground_Chunk_Shader::getUniformLocations()
    {
        m_locationViewMatrix        = glGetUniformLocation ( getId(), "viewMatrix"          );
        m_locationModelMatrix       = glGetUniformLocation ( getId(), "modelMatrix"         );
        m_locationProjectionMatrix  = glGetUniformLocation ( getId(), "projectionMatrix"    );

        m_skyColourLocation = glGetUniformLocation ( getId(), "skyColour" );
    }
}
