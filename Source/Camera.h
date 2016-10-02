#ifndef CAMERA_H
#define CAMERA_H

#include "OpenGL/GLM/glm_transformations.h"

class Camera
{
    public:
        void move ( float dt );

        const Vector3& getPosition () const;
        const Vector3& getRotation () const;

        void movePosition ( const Vector3& position );

   // private:
        Vector3 m_position;
        Vector3 m_rotation;
};

#endif // CAMERA_H
