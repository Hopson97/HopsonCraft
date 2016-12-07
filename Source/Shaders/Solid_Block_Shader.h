#ifndef Solid_Block_Shader_H
#define Solid_Block_Shader_H

#include "Chunk_Shader.h"

class Entity;

namespace Shader
{
    class Solid_Block_Shader : public Chunk_Shader
    {
        public:
            Solid_Block_Shader();

        private:
            void bindAttributes     () override;
            void getUniformLocations() override;
    };
}

#endif // Solid_Block_Shader_H
