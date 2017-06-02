#include "AABB.h"


AABB::AABB(const Vector3& dimension)
:   m_dimensions (dimension)
{ }

void AABB::update(const Vector3& position)
{
    m_min = position;
    m_max = m_min + m_dimensions;
}

bool AABB::isCollidingWith(const AABB& other)
{
    return  (m_min.x <= other.m_max.x && m_max.x >= m_min.x) &&
            (m_min.y <= other.m_max.y && m_max.y >= m_min.y) &&
            (m_min.z <= other.m_max.z && m_max.z >= m_min.z);
}


Vector3 AABB::getVN(const Vector3& normal) const
{
    Vector3 res = m_min;

    if (normal.x < 0)
    {
        res.x += m_dimensions.x;
    }
    if (normal.y < 0)
    {
        res.y += m_dimensions.y;
    }
    if (normal.z < 0)
    {
        res.z += m_dimensions.z;
    }

    return res;
}

Vector3 AABB::getVP(const Vector3& normal) const
{
    Vector3 res = m_min;

    if (normal.x > 0)
    {
        res.x += m_dimensions.x;
    }
    if (normal.y > 0)
    {
        res.y += m_dimensions.y;
    }
    if (normal.z > 0)
    {
        res.z += m_dimensions.z;
    }

    return res;
}
