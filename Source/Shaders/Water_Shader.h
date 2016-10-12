#ifndef WATER_SHADER_H
#define WATER_SHADER_H

#include "Shader_Program.h"

class Water_Shader : public Shader_Program
{
    public:
        Water_Shader();

        void loadModelMatrix        ( const Matrix4& modelMatrix    );
        void loadViewMatrix         ( const Camera&  camera         );
        void loadProjMatrix         ( const Matrix4& projMatrix     );

        void loadTime   ( float time );

    private:
        void bindAttibs () override;
        void getUniformLocations () override;

        GLuint m_locationViewMatrix;
        GLuint m_locationModelMatrix;
        GLuint m_locationProjectionMatrix;

        GLuint m_timeLocation;

};

#endif // WATER_SHADER_H
