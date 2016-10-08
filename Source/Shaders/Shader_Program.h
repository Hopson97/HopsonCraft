#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <string>

#include "OpenGL/Glew/glew.h"
#include "OpenGL/Glm/glm_transformations.h"

class Camera;

class Shader_Program
{
    public:
        Shader_Program  ( const std::string& vertexFile, const std::string& fragmentFile );
        ~Shader_Program ();

        void start  () const;
        void stop   () const;

        GLuint getId () const;

    protected:
        void loadMatrix4 ( GLuint location, const Matrix4& matrix ) const;


        void bindAttrib ( GLuint location, const char* name );

        virtual void bindAttibs () = 0;
        virtual void getUniformLocations () = 0;

    private:
        GLuint m_shaderProgram;
};

#endif // SHADER_PROGRAM_H
