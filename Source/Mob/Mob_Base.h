#ifndef MOB_BASE_H_INCLUDED
#define MOB_BASE_H_INCLUDED

#include "../Entity/Entity.h"

class Mob : public Entity
{
    public:
        void update     (float dt);
        void addForce   (const Vector3& force);

    protected:
        virtual void onUpdate(float dt) = 0;

    private:
        bool isDead = false;

        Vector3 m_velocity;
};

#endif // MOB_BASE_H_INCLUDED
