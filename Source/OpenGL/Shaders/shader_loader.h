#ifndef SHADER_LOADER_H_INCLUDED
#define SHADER_LOADER_H_INCLUDED

#include "../GLEW/glew.h"

#include <string>

namespace GL
{
    namespace Shader
    {
        GLuint load( const std::string& vertexFilePath,
                     const std::string& fragmentFilePath );
    }
}


#endif // SHADER_LOADER_H_INCLUDED
