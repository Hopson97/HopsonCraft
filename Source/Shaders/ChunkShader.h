#ifndef ChunkShader_H_INCLUDED
#define ChunkShader_H_INCLUDED

#include "SimpleShader.h"

class ChunkShader : public SimpleShader
{
    public:
        ChunkShader(std::string&& vertexShaderFile);

        void loadTimer(float time);

        void getUniformLocations() override;

    private:
        GLuint m_locationTimer;
        GLuint m_locationMaxLightValue;
};

#endif // ChunkShader_H_INCLUDED
