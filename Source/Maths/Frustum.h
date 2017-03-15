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

        //void setInterals(float angle, float ratio, float nearPlane, float farPlane);

        void update(const Matrix4& projView);

        bool pointInFrustum(const Vector3& point) const;
        bool boxInFrustum(const AABB& box) const;


    private:
/*
        Vector3 m_ntl,
                m_ntr,
                m_nbl,
                m_nbr,
                m_ftl,
                m_ftr,
                m_fbl,
                m_fbr;

        float m_farPlane,
              m_nearPlane,
              m_fov,
              m_ratio;
*/


        std::array<Plane, 6> m_planes;
};








#endif // PRAGMA_H_INCLUDE
