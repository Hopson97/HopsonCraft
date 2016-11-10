#ifndef FLORA_SHADER_H
#define FLORA_SHADER_H

#include "Shader.h"

class Camera;

namespace Shader
{
    class Flora_Shader : public Shader_Program
    {
        public:
            Flora_Shader();

            void loadCameraMatrix   (const Camera& camera);
            void loadChunkMatrix    (const Matrix4& matrix);
            void loadSkyColour      ( const Vector3& skyColour );

        private:
            void bindAttributes() override;
            void getUniformLocations() override;

            GLuint m_locationViewMatrix;
            GLuint m_locationModelMatrix;
            GLuint m_locationProjectionMatrix;
            GLuint m_skyColourLocation;
    };
}

#endif // FLORA_SHADER_H
