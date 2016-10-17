#ifndef CHUNK_SHADER_H
#define CHUNK_SHADER_H

#include "Shader_Program.h"

class Chunk_Shader : public Shader_Program
{
    public:
        Chunk_Shader();

        void loadModelMatrix        ( const Matrix4& modelMatrix    );
        void loadViewMatrix         ( const Camera&  camera         );
        void loadProjMatrix         ( const Matrix4& projMatrix     );

        void loadIsPlayerLocation   ( int isLocation                );
        void loadSkyColour          ( const Vector3& skyColour      );

    private:
        void bindAttibs () override;
        void getUniformLocations () override;

        GLuint m_locationViewMatrix;
        GLuint m_locationModelMatrix;
        GLuint m_locationProjectionMatrix;
        GLuint m_skyColourLocation;

        GLuint m_chunkLocation;
};

#endif // CHUNK_SHADER_H
