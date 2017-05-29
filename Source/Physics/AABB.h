#ifndef AABB_H_INCLUDED
#define AABB_H_INCLUDED

#include <cstdint>

#include "../Glm_Common.h"


struct AABB
{
    public:
        AABB(const Vector3& dimensions);

        bool isCollidingWith (const AABB& other);

        void update(const Vector3& position);

        Vector3 getVN(const Vector3& normal) const;
        Vector3 getVP(const Vector3& normal) const;

        const Vector3& getDimensions() const { return m_dimensions; }

    private:
        Vector3 m_min;
        Vector3 m_max;
        Vector3 m_dimensions;
};

#endif // AABB_H_INCLUDED
