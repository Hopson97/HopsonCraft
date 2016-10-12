#include "Water_Shader.h"

#include <iostream>

#include "Camera.h"
#include "Maths.h"

Water_Shader :: Water_Shader ()
:   Shader_Program  ( "Water_Vertex", "Water_Fragment" )
{
    bindAttibs();
    getUniformLocations();
}

void Water_Shader :: loadModelMatrix(const Matrix4& modelMatrix )
{
    loadMatrix4( m_locationModelMatrix, modelMatrix );
}

void Water_Shader :: loadViewMatrix(const Camera& camera)
{
    loadMatrix4 ( m_locationViewMatrix, Maths::createViewMatrix( camera ) );
}

void Water_Shader :: loadProjMatrix(const Matrix4& projMatrix)
{
    loadMatrix4( m_locationProjectionMatrix, projMatrix );
}

void Water_Shader :: loadTime ( float time )
{
    loadFloat( m_timeLocation, time );
}

void Water_Shader :: bindAttibs()
{
    bindAttrib( 0, "vertexPosition"  );
    bindAttrib( 1, "texturePosition" );
}

void Water_Shader :: getUniformLocations()
{
    m_locationViewMatrix        = glGetUniformLocation ( getId(), "viewMatrix"          );
    m_locationModelMatrix       = glGetUniformLocation ( getId(), "modelMatrix"         );
    m_locationProjectionMatrix  = glGetUniformLocation ( getId(), "projectionMatrix"    );

    m_timeLocation  = glGetUniformLocation ( getId(), "time" );

}
