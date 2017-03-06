#include "Mob_Base.h"

void Mob::update(float dt)
{
    position += m_velocity * dt;
    m_velocity *= 0.95;
    onUpdate(dt);
}

void Mob::addForce(const Vector3& force)
{
    m_velocity += force;
}
