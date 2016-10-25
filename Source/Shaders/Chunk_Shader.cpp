#include "Chunk_Shader.h"

#include <iostream>

#include "Camera.h"
#include "Maths/Matrix_Maths.h"

Chunk_Shader :: Chunk_Shader ()
:   Shader_Program  ( "Chunk_Vertex", "Chunk_Fragment" )
{
    bindAttibs();
    getUniformLocations();
}

void Chunk_Shader :: loadModelMatrix(const Matrix4& modelMatrix )
{
    loadMatrix4( m_locationModelMatrix, modelMatrix );
}

void Chunk_Shader :: loadViewMatrix(const Camera& camera)
{
    loadMatrix4 ( m_locationViewMatrix, Maths::createViewMatrix( camera ) );
}

void Chunk_Shader :: loadProjMatrix(const Matrix4& projMatrix)
{
    loadMatrix4( m_locationProjectionMatrix, projMatrix );
}

void Chunk_Shader :: loadIsPlayerLocation ( int isLocation )
{
    loadInteger( m_chunkLocation, isLocation );
}

void Chunk_Shader :: loadSkyColour ( const Vector3& skyColour )
{
    loadVector3 ( m_skyColourLocation, skyColour );
}

void Chunk_Shader :: bindAttibs()
{
    bindAttrib( 0, "vertexPosition"  );
    bindAttrib( 1, "texturePosition" );
}

void Chunk_Shader :: getUniformLocations()
{
    m_locationViewMatrix        = glGetUniformLocation ( getId(), "viewMatrix"          );
    m_locationModelMatrix       = glGetUniformLocation ( getId(), "modelMatrix"         );
    m_locationProjectionMatrix  = glGetUniformLocation ( getId(), "projectionMatrix"    );

    m_chunkLocation             = glGetUniformLocation ( getId(), "isLocation"  );
    m_skyColourLocation         = glGetUniformLocation ( getId(), "skyColour"   );

}
