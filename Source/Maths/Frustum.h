#ifndef PRAGMA_H_INCLUDE
#define PRAGMA_H_INCLUDE

#include "../Glm_Common.h"

#include <array>

struct Plane
{
    float   distance;
    Vector3 normal;
};


class Frustum
{
    public:
        void update(const Matrix4& projView);

    private:
        std::array<Plane, 6> m_planes;
};








#endif // PRAGMA_H_INCLUDE
