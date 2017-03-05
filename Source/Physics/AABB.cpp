#include "AABB.h"


AABB::AABB(const Vector3& dimensions)
:   m_dimensions (dimensions)
{ }

void AABB::update(const Vector3& position)
{
    m_position = position;
}
