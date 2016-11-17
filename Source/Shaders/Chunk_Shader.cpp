#include "Chunk_Shader.h"

#include <iostream>

#include "../Maths/Matrix_Maths.h"
#include "../Player/Camera.h"

namespace Shader
{
    Chunk_Shader::Chunk_Shader(const std::string& vertexShaderFile, const std::string& fragmentShaderFile)
    :   Shader_Program  (vertexShaderFile, fragmentShaderFile)
    {
        getUniformLocations();
        bindAttributes();

        useProgram();
        loadMatrix4(m_locationProjectionMatrix, Maths::createPerspectiveMatrix());
        glUseProgram(0);
    }

    void Chunk_Shader::loadCameraMatrix(const Camera& camera) const
    {
        loadMatrix4(m_locationViewMatrix, Maths::createViewMatrix(camera));
    }

    void Chunk_Shader::loadChunkMatrix(const Matrix4& matrix) const
    {
        loadMatrix4(m_locationModelMatrix, matrix);
    }

    void Chunk_Shader::loadSkyColour ( const Vector3& skyColour ) const
    {
        loadVector3 (m_skyColourLocation, skyColour);
    }

    void Chunk_Shader::bindAttributes()
    {
        bindAttribute(0, "inVertexCoords");
        bindAttribute(1, "inTextureCoords");
    }

    void Chunk_Shader::getUniformLocations()
    {
        m_locationViewMatrix        = glGetUniformLocation (getId(), "viewMatrix");
        m_locationModelMatrix       = glGetUniformLocation (getId(), "modelMatrix");
        m_locationProjectionMatrix  = glGetUniformLocation (getId(), "projectionMatrix");

        m_skyColourLocation         = glGetUniformLocation (getId(), "skyColour");
    }

}
