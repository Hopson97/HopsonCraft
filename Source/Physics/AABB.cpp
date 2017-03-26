#include "AABB.h"


AABB::AABB(const Vector3& dimension)
:   dimensions (dimension)
{ }

void AABB::update(const Vector3& position)
{
    point = position;
}


Vector3 AABB::getVN(const Vector3& normal) const
{
    Vector3 res = point;

    if (normal.x < 0)
    {
        res.x += dimensions.x;
    }
    if (normal.y < 0)
    {
        res.y += dimensions.y;
    }
        if (normal.z < 0)
    {
        res.z += dimensions.z;
    }

    return res;
}

Vector3 AABB::getVP(const Vector3& normal) const
{
    Vector3 res = point;

    if (normal.x > 0)
    {
        res.x += dimensions.x;
    }
    if (normal.y > 0)
    {
        res.y += dimensions.y;
    }
        if (normal.z > 0)
    {
        res.z += dimensions.z;
    }

    return res;
}
