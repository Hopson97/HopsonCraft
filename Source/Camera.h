#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include "Entity.h"
#include "OpenGL/GL_Maths.h"

class Camera : public Entity
{
    public:
        Vector3 keyboardInput   (float speed);
        void mouseInput         ();
        void movePosition       (const Vector3& amount);

};

#endif // CAMERA_H_INCLUDED
