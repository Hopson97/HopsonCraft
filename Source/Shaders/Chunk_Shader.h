#ifndef CHUNK_SHADER_H
#define CHUNK_SHADER_H

#include "Shader.h"

class Entity;
class Camera;

namespace Shader
{
    class Chunk_Shader : public Shader_Program
    {
        public:
            Chunk_Shader(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);
            virtual ~Chunk_Shader() = default;

            void loadCameraMatrix   (const Camera& camera) const;
            void loadChunkMatrix    (const Matrix4& matrix) const;
            void loadSkyColour      (const Vector3& skyColour) const;
            void loadMaxLightValue  (int value) const;

        protected:
            virtual void bindAttributes     () override;
            virtual void getUniformLocations() override;

        private:

            GLuint m_locationViewMatrix;
            GLuint m_locationModelMatrix;
            GLuint m_locationProjectionMatrix;
            GLuint m_skyColourLocation;
            GLuint m_maxLightValueLocation;
    };
}

#endif // CHUNK_SHADER_H
