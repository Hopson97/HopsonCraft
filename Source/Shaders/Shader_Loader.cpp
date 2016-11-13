#include "Shader_Loader.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <stdexcept>

namespace Shader
{
    namespace
    {
        void checkErrors(GLuint shaderId, GLenum statusType, const std::string& errorType)
        {
            auto bufferSize = 512;

            GLint isSuccess;
            GLchar infoLog[bufferSize];

            glGetShaderiv (shaderId, statusType, &isSuccess);
            if (!isSuccess)
            {
                glGetShaderInfoLog (shaderId, bufferSize, nullptr, infoLog);
                throw std::runtime_error ("Shader loading error.\nType: " + errorType + "\nWhat: " + infoLog);
            }
        }

        std::string getSource (const std::string& shaderFile)
        {
            std::ifstream shaderSourceFile ("Shaders/" + shaderFile + ".glsl");
            if (!shaderSourceFile.is_open())
            {
                throw std::runtime_error ("Unable to open the shader file: " + shaderFile + ".glsl");
            }
            shaderSourceFile.exceptions(std::ifstream::badbit);

            std::string source;
            std::stringstream stream;

            try
            {
                stream << shaderSourceFile.rdbuf();
                source = stream.str();
            }
            catch ( std::ifstream::failure& e)
            {
                throw std::runtime_error ("Unable to read the shader file: " + shaderFile + ".glsl");
            }

            return source;
        }

        GLuint compileShader (const char* source, GLenum type)
        {
            auto shaderId = glCreateShader(type);

            glShaderSource  (shaderId, 1, &source, nullptr);
            glCompileShader (shaderId);

            checkErrors(shaderId, GL_COMPILE_STATUS, "Error compiling shader!");

            return shaderId;
        }

        GLuint createProgram(GLuint vertexShaderId, GLuint fragmentShaderId)
        {
            auto shaderProgrsm = glCreateProgram();

            glAttachShader (shaderProgrsm, vertexShaderId);
            glAttachShader (shaderProgrsm, fragmentShaderId);
            glLinkProgram  (shaderProgrsm);

            return shaderProgrsm;
        }
    }

    GLuint load (const std::string& vertexShaderFile, const std::string& fragmentShaderFile)
    {
        auto vertexSource    = getSource (vertexShaderFile);
        auto fragmentSource  = getSource (fragmentShaderFile);

        auto vertexId   = compileShader(vertexSource.c_str(),   GL_VERTEX_SHADER);
        auto fragmentId = compileShader(fragmentSource.c_str(), GL_FRAGMENT_SHADER);

        auto shaderProgramId = createProgram(vertexId, fragmentId);

        glDeleteShader(vertexId);
        glDeleteShader(fragmentId);

        return shaderProgramId;
    }
} //Namespace Shader
