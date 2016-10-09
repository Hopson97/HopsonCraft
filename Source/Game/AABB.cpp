#include "AABB.h"

AABB::AABB(const Vector3& size)
:   m_size ( size)
{ }

void AABB::setPosition(const Vector3& position)
{
    m_position = position;
}
