#include "Screen_Shader.h"

namespace Shader
{
    Screen_Shader::Screen_Shader(const std::string& vertexFile, const std::string& fragmentFile)
    :   Shader_Program (vertexFile, fragmentFile)
    {
        bindAttributes();
    }

    void Screen_Shader::bindAttributes()
    {
        bindAttribute(0, "inVertexCoords");
        bindAttribute(1, "inTextureCoords");
    }
}
