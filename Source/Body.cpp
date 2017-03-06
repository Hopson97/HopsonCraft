#include "Body.h"

void Body::addForce(const Vector3& force)
{
    m_velocity += force;
}

void Body::update(float dt)
{
    position += m_velocity * dt;

    if (position.x < 0.1)
    {
        position.x = 0.1;
    }
    if (position.z < 0.1)
    {
        position.z = 0.1;
    }

    m_velocity *= 0.98;
}
