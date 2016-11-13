#ifndef SHADER_LOADER_H_INCLUDED
#define SHADER_LOADER_H_INCLUDED

#include "../OpenGL/Glew/glew.h"

#include <string>

namespace Shader
{
    GLuint load (const std::string& vertexShaderFile, const std::string& fragmentShaderFile);
} //Namespace Shader

#endif // SHADER_LOADER_H_INCLUDED
