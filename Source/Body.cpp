#include "Body.h"

void Body::addForce(const Vector3& force)
{
    m_velocity += force;
}

void Body::update(float dt)
{
    position += m_velocity * dt;
    m_velocity *= 0.98;
}
