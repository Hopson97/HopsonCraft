#include "Chunk_Shader.h"

#include "Maths/Matrix_Maths.h"
#include "Camera.h"

namespace Shader
{
    Ground_Chunk_Shader::Ground_Chunk_Shader(const std::string& vertexShaderFile, const std::string& fragmentShaderFile)
    :   Shader_Program (vertexShaderFile, fragmentShaderFile)
    {
        bindAttributes();
        getUniformLocations();

        useProgram();
        loadMatrix4(m_projectionMatrixLocation, Maths::createPerspectiveMatrix());
        glUseProgram(0);
    }

    void Ground_Chunk_Shader::loadCameraMatrix(const Camera& camera)
    {
        loadMatrix4(m_viewMatrixLocation, Maths::createViewMatrix(camera));
    }

    void Ground_Chunk_Shader::loadChunkMatrix(const Matrix4& matrix)
    {
        loadMatrix4(m_modelMatrixLocation, matrix);
    }

    void Ground_Chunk_Shader::bindAttributes()
    {
        bindAttribute(0, "inVertexCoords");
        bindAttribute(1, "inTextureCoords");
    }

    void Ground_Chunk_Shader::getUniformLocations()
    {
        m_viewMatrixLocation        = glGetUniformLocation(getId(), "viewMatrix");
        m_modelMatrixLocation       = glGetUniformLocation(getId(), "modelMatrix");
        m_projectionMatrixLocation  = glGetUniformLocation(getId(), "projectionMatrix");
    }
}
