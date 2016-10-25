#ifndef WATER_SHADER_H
#define WATER_SHADER_H

#include "Shader.h"

class Camera;

namespace Shader
{
    class Water_Shader : public Shader_Program
    {
        public:
            Water_Shader();

            void loadCameraMatrix   (const Camera& camera);
            void loadChunkMatrix    (const Matrix4& matrix);
            void loadSkyColour      ( const Vector3& skyColour );
            void loadTime           (float time);


        private:
            void bindAttributes     () override;
            void getUniformLocations() override;


            GLuint m_locationViewMatrix;
            GLuint m_locationModelMatrix;
            GLuint m_locationProjectionMatrix;

            GLuint m_timeLocation;
            GLuint m_skyColourLocation;
    };
}


#endif // WATER_SHADER_H
