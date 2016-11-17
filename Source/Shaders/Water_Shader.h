#ifndef WATER_SHADER_H
#define WATER_SHADER_H

#include "Chunk_Shader.h"

class Camera;

namespace Shader
{
    class Water_Shader : public Chunk_Shader
    {
        public:
            Water_Shader();

            void loadTime (float time) const;

        private:
            void bindAttributes     () override;
            void getUniformLocations() override;

            GLuint m_timeLocation;

    };
}


#endif // WATER_SHADER_H
