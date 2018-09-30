#ifndef AABB_H_INCLUDED
#define AABB_H_INCLUDED

#include <cstdint>

#include "../Maths/GLM.h"


struct AABB
{
    public:
        AABB(const Vector3& dimensions) noexcept;

        bool isCollidingWith (const AABB& other) noexcept;

        void update(const Vector3& position) noexcept;

        Vector3 getVN(const Vector3& normal) const noexcept;
        Vector3 getVP(const Vector3& normal) const noexcept;

        const Vector3& getDimensions() const noexcept { return m_dimensions; }

    private:
        Vector3 m_min;
        Vector3 m_max;
        Vector3 m_dimensions;
};

#endif // AABB_H_INCLUDED
