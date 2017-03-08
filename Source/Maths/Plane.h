#ifndef PLANE_H_INCLUDED
#define PLANE_H_INCLUDED

#include "../Glm_Common.h"

class Plane
{
    public:
        Plane();
    private:
        Vector3 m_point, m_normal;
};

#endif // PLANE_H_INCLUDED
