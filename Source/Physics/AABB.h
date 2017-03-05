#ifndef AABB_H_INCLUDED
#define AABB_H_INCLUDED

#include <cstdint>

#include "../Glm_Common.h"

class AABB
{
    public:
        AABB(const Vector3& dimensions);

        void update(const Vector3& position);

    private:
        Vector3 m_position;
        Vector3 m_dimensions;
};

#endif // AABB_H_INCLUDED
