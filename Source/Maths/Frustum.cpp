#include "Frustum.h"

namespace Planes
{
    enum
    {
        Near = 0,
        Far,
        Left,
        Right,
        Top,
        Bottom
    };
}

float Plane::distanceToPoint(const Vector3& point) const
{
    return glm::dot(point, normal) + distance;
}


//calcuate matrix based on the projection * view matrix.
void Frustum::update(const Matrix4& mat)
{
    // left
    m_planes[Planes::Left].normal.x     = mat[0][3] + mat[0][0];
    m_planes[Planes::Left].normal.y     = mat[1][3] + mat[1][0];
    m_planes[Planes::Left].normal.z     = mat[2][3] + mat[2][0];
    m_planes[Planes::Left].distance     = mat[3][3] + mat[3][0];

    // right
    m_planes[Planes::Right].normal.x    = mat[0][3] - mat[0][0];
    m_planes[Planes::Right].normal.y    = mat[1][3] - mat[1][0];
    m_planes[Planes::Right].normal.z    = mat[2][3] - mat[2][0];
    m_planes[Planes::Right].distance    = mat[3][3] - mat[3][0];

    // bottom
    m_planes[Planes::Bottom].normal.x   = mat[0][3] + mat[0][1];
    m_planes[Planes::Bottom].normal.y   = mat[1][3] + mat[1][1];
    m_planes[Planes::Bottom].normal.z   = mat[2][3] + mat[2][1];
    m_planes[Planes::Bottom].distance   = mat[3][3] + mat[3][1];

    // top
    m_planes[Planes::Top].normal.x      = mat[0][3] - mat[0][1];
    m_planes[Planes::Top].normal.y      = mat[1][3] - mat[1][1];
    m_planes[Planes::Top].normal.z      = mat[2][3] - mat[2][1];
    m_planes[Planes::Top].distance      = mat[3][3] - mat[3][1];

    // near
    m_planes[Planes::Near].normal.x     = mat[0][3] + mat[0][2];
    m_planes[Planes::Near].normal.y     = mat[1][3] + mat[1][2];
    m_planes[Planes::Near].normal.z     = mat[2][3] + mat[2][2];
    m_planes[Planes::Near].distance     = mat[3][3] + mat[3][2];

    // far
    m_planes[Planes::Far].normal.x      = mat[0][3] - mat[0][2];
    m_planes[Planes::Far].normal.y      = mat[1][3] - mat[1][2];
    m_planes[Planes::Far].normal.z      = mat[2][3] - mat[2][2];
    m_planes[Planes::Far].distance      = mat[3][3] - mat[3][2];

    for (uint32_t i = 0; i < 6; i++)
    {
        float length = glm::length(m_planes[i].normal);
        m_planes[i].normal      /= length;
        m_planes[i].distance    /= length;
    }
}


bool Frustum::pointInFrustum(const Vector3& point) const
{
    for (uint32_t i = 0; i < 6; i++)
    {
        if (m_planes[i].distanceToPoint(point) < 0)
        {
            return false;
        }
    }
    return true;
}

bool Frustum::boxInFrustum(const AABB& box) const
{
    Vector3 min = box.point;
    Vector3 max = { box.point.x + box.dimensions.x,
                    box.point.y + box.dimensions.y,
                    box.point.z + box.dimensions.z };

    for (uint32_t i = 0; i < 6; i++)
    {
        if(m_planes[i].distanceToPoint(min) < 0 ||
           m_planes[i].distanceToPoint(max) < 0)
        {
            return false;
        }
    }
    return true;
}























