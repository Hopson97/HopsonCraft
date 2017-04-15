#include "Solid_Shader.h"

#include "../Maths/Matrix_Maths.h"

namespace Shader
{
    Solid_Shader::Solid_Shader()
    :   Simple_Shader   ("Solid", "Block")
    {
        getUniformLocations();
    }
}
