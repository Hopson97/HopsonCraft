#include "Screen_Shader.h"

namespace Shader
{
    Screen_Shader::Screen_Shader()
    :   Shader_Program ("Simple_Vertex", "Simple_Fragment")
    {
        bindAttributes();
    }

    void Screen_Shader::bindAttributes()
    {
        bindAttribute(0, "inVertexCoords");
        bindAttribute(1, "inTextureCoords");
    }
}
