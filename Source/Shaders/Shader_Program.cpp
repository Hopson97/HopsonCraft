#include "Shader_Program.h"

#include "Shader_Loader.h"

Shader_Program::Shader_Program ( const std::string& vertexFile, const std::string& fragmentFile )
:   m_shaderProgram  ( loadShader( "Shaders/" + vertexFile  + ".glsl", "Shaders/" + fragmentFile  + ".glsl" ) )
{ }

Shader_Program :: ~Shader_Program()
{
    glDeleteProgram ( m_shaderProgram );
}

void Shader_Program :: start () const
{
    glUseProgram ( m_shaderProgram );
}

void Shader_Program :: stop () const
{
    glUseProgram ( 0 );
}

GLuint Shader_Program :: getId () const
{
    return m_shaderProgram;
}


void Shader_Program :: loadMatrix4 ( GLuint location, const Matrix4& matrix ) const
{
    glUniformMatrix4fv ( location, 1, GL_FALSE, glm::value_ptr( matrix ) );
}


void Shader_Program::bindAttrib ( GLuint location, const char* name )
{
    glBindAttribLocation ( m_shaderProgram, location, name );
}
