#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include "Entity.h"

class Camera : public Entity
{
    public:
        Camera();
        void update ();
        void hookEntity(const Entity& entity);

    private:
        const Entity* m_P_entity = this;
};

#endif // CAMERA_H_INCLUDED
