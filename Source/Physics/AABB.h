#ifndef AABB_H_INCLUDED
#define AABB_H_INCLUDED

#include <cstdint>

#include "../Glm_Common.h"


class AABB
{
    public:
        AABB(const Vector3& dimensions);

        void update(const Vector3& position);

        Vector3 getPoint() const { return m_point;      };
        Vector3 getDim  () const { return m_dimensions; };



    private:
        Vector3 m_point;
        Vector3 m_dimensions;
};

#endif // AABB_H_INCLUDED
