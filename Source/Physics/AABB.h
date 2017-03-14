#ifndef AABB_H_INCLUDED
#define AABB_H_INCLUDED

#include <cstdint>

#include "../Glm_Common.h"


struct AABB
{
    public:
        AABB(const Vector3& dimensions);

        void update(const Vector3& position);

        Vector3 point;
        Vector3 dimensions;
};

#endif // AABB_H_INCLUDED
