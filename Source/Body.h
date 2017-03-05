#ifndef BODY_H_INCLUDED
#define BODY_H_INCLUDED

#include "Entity.h"

class Body : public Entity
{
    public:
        void addForce   (const Vector3& force);
        void update     (float dt);

    private:
        Vector3 m_velocity;
};

#endif // BODY_H_INCLUDED
