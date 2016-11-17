#ifndef FLORA_SHADER_H
#define FLORA_SHADER_H

#include "Chunk_Shader.h"

class Camera;

namespace Shader
{
    class Flora_Shader : public Chunk_Shader
    {
        public:
            Flora_Shader();

        private:
            void bindAttributes() override;
            void getUniformLocations() override;
    };
}

#endif // FLORA_SHADER_H
