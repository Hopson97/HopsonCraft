#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include "Entity.h"

class Camera : public Entity
{
    public:
        Camera();

        Vector3 input  ();
        void update (float dt);

    private:
        void mouseInput();
};

#endif // CAMERA_H_INCLUDED
