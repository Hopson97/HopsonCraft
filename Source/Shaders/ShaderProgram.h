#ifndef ShaderProgram_H_INCLUDED
#define ShaderProgram_H_INCLUDED
#include "../glad/glad.h"
#include <string>

#include "../Maths/GLM.h"

class ShaderProgram
{
    public:
        ShaderProgram(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);
        virtual ~ShaderProgram();

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

#endif // ShaderProgram_H_INCLUDED
