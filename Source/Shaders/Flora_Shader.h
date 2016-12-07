#ifndef FLORA_SHADER_H
#define FLORA_SHADER_H

#include "Chunk_Shader.h"

class Entity;

namespace Shader
{
    class Flora_Shader : public Chunk_Shader
    {
        public:
            Flora_Shader();

            void loadTime (float time) const;

        private:
            void bindAttributes() override;
            void getUniformLocations() override;

            GLuint m_locationTime;
    };
}

#endif // FLORA_SHADER_H
