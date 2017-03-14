#include "AABB.h"


AABB::AABB(const Vector3& dimensions)
:   dimensions (dimensions)
{ }

void AABB::update(const Vector3& position)
{
    point = position;
}

