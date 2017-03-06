#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>

#include "../OpenGL/GL_Maths.h"

namespace Shader
{
    class Shader_Program
    {
        public:
            Shader_Program  () = default;
            Shader_Program  (const std::string& vertexShaderFile, const std::string& fragmentShaderFile);
            virtual ~Shader_Program ();

            void create (const std::string& vertexShaderFile, const std::string& fragmentShaderFile);

            void useProgram () const;

        protected:
            GLuint getId() const;

            void loadMatrix4 (GLuint location, const Matrix4& matrix)   const;
            void loadVector3 (GLuint location, const Vector3& vect)     const;

            void loadInteger (GLuint location, int data)    const;
            void loadFloat   (GLuint location, float data)  const;

            void bindAttribute(GLuint location, const std::string& name);

            virtual void bindAttributes() = 0;
            virtual void getUniformLocations() = 0;

        private:
            GLuint m_shaderProgram = 0;

    };
} //Namespace Shader

#endif // SHADER_H
