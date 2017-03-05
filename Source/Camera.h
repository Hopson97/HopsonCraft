#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include "Entity.h"

class Camera : public Entity
{
    public:
        void input  ();
        void update (float dt);

        const Vector3& getVelocity() const;

    private:
        void mouseInput();
        Vector3 m_velocity;

};

#endif // CAMERA_H_INCLUDED
