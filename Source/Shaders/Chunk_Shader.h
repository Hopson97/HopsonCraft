#ifndef GROUND_CHUNK_SHADER_H
#define GROUND_CHUNK_SHADER_H

#include "Shader.h"

class Camera;

namespace Shader
{
    class Ground_Chunk_Shader : public Shader_Program
    {
        public:
            Ground_Chunk_Shader(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);

            void loadCameraMatrix   (const Camera& camera);
            void loadChunkMatrix    (const Matrix4& matrix);

        private:
            void bindAttributes() override;
            void getUniformLocations() override;

            GLuint m_viewMatrixLocation;
            GLuint m_modelMatrixLocation;
            GLuint m_projectionMatrixLocation;
    };
}

#endif // GROUND_CHUNK_SHADER_H
