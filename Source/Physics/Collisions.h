#ifndef COLLISIONS_H_INCLUDED
#define COLLISIONS_H_INCLUDED

#include "../Glm_Common.h"

class AABB;

namespace Collision
{
    bool pointInAABB(const Vector3& point, const AABB& box);

    bool xAABB(const AABB& left, const AABB& right);
    bool zAABB(const AABB& back, const AABB& front);
    bool yAABB(const AABB& top, const AABB& bottom);
}

#endif // COLLISIONS_H_INCLUDED
