#ifndef SKYBOX_SHADER_H_INCLUDED
#define SKYBOX_SHADER_H_INCLUDED

#include "Shader.h"

class Entity;
class Camera;

namespace Shader
{
    class Skybox_Shader : public Shader_Program
    {
        public:
            Skybox_Shader();

            void loadCameraMatrix   (const Camera& camera) const;

        private:
            virtual void bindAttributes     () override;
            virtual void getUniformLocations() override;

            GLuint m_locationViewMatrix;
            GLuint m_locationProjectionMatrix;

    };
}

#endif // SKYBOX_SHADER_H_INCLUDED
