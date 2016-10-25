#ifndef GROUND_CHUNK_SHADER_H
#define GROUND_CHUNK_SHADER_H

#include "Shader.h"

class Camera;

namespace Shader
{
    class Ground_Chunk_Shader : public Shader_Program
    {
        public:
            Ground_Chunk_Shader();

            void loadCameraMatrix   (const Camera& camera);
            void loadChunkMatrix    (const Matrix4& matrix);
            void loadSkyColour      ( const Vector3& skyColour );

        private:
            void bindAttributes     () override;
            void getUniformLocations() override;

            GLuint m_locationViewMatrix;
            GLuint m_locationModelMatrix;
            GLuint m_locationProjectionMatrix;
            GLuint m_skyColourLocation;
    };
}

#endif // GROUND_CHUNK_SHADER_H
