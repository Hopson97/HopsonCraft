#ifndef PRAGMA_H_INCLUDE
#define PRAGMA_H_INCLUDE

#include "../Glm_Common.h"
#include "../Physics/AABB.h"

#include <array>

struct Plane
{
    float   distance;
    Vector3 normal;

    float distanceToPoint(const Vector3& point) const;
};


class Frustum
{
    public:
        void update(const Matrix4& projView);

        bool pointInFrustum(const Vector3& point) const;
        bool boxInFrustum(const AABB& box) const;


    private:
        std::array<Plane, 6> m_planes;
};








#endif // PRAGMA_H_INCLUDE
