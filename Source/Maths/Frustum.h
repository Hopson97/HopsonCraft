#ifndef PRAGMA_H_INCLUDE
#define PRAGMA_H_INCLUDE

#include "GLM.h"
#include "../Physics/AABB.h"

#include <array>

struct Plane
{
    float   distance;
    Vector3 normal;

    float distanceToPoint(const Vector3& point) const noexcept;
};


class Frustum
{
    public:
        void update(const Matrix4& projView) noexcept;

        bool pointInFrustum(const Vector3& point) const noexcept;
        bool boxInFrustum(const AABB& box) const noexcept;


    private:
        std::array<Plane, 6> m_planes;
};








#endif // PRAGMA_H_INCLUDE
