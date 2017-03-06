#include "Solid_Block_Shader.h"

#include "../Maths/Matrix_Maths.h"
#include "../Entity.h"

namespace Shader
{
    Solid_Block_Shader::Solid_Block_Shader()
    :   Chunk_Shader ("Ground_Vertex", "Ground_Fragment")
    {
        getUniformLocations();
    }

    void Solid_Block_Shader::bindAttributes()
    { }

    void Solid_Block_Shader::getUniformLocations()
    { }
}
