#ifndef SHADER_PROGRAM_H_INCLUDED
#define SHADER_PROGRAM_H_INCLUDED
#include <GL/glew.h>
#include <GL/glew.h>
#include <string>

#include "../Glm_Common.h"

namespace Shader
{
    class Shader_Program
    {
        public:
            Shader_Program(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);
            virtual ~Shader_Program();

            void bind   ();
            void unbind ();

        protected:
            virtual void getUniformLocations () = 0;

            GLuint getID() const;

            void loadInt    (GLuint location, int value);
            void loadFloat  (GLuint location, float value);
            void loadVector2(GLuint location, const Vector2& vector);
            void loadMatrix4(GLuint location, const Matrix4& matrix);

        private:
            GLuint m_programID;
    };
}

#endif // SHADER_PROGRAM_H_INCLUDED
