#ifndef SCREEN_SHADER_H
#define SCREEN_SHADER_H

#include "Shader.h"

namespace Shader
{
    class Screen_Shader : public Shader_Program
    {
        public:
            Screen_Shader();

        private:
            void bindAttributes() override;
            void getUniformLocations() override {}
    };
}


#endif // SCREEN_SHADER_H
