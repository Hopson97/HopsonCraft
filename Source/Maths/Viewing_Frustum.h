#ifndef VIEWING_FRUSTUM_H_INCLUDED
#define VIEWING_FRUSTUM_H_INCLUDED

#include "OpenGL/Glm/glm_transformations.h"

class Box
{
    public:
        Box ( const Vector3& corner, float x, float y, float z )
        {
            set ( corner, x, y, z );
        }

        void set( const Vector3& corner, float x, float y, float z )
        {
            m_corner = corner;
            m_x = x;
            m_y = y;
            m_z = z;
        }

    private:
        Vector3 m_corner;
        float m_x, m_y, m_z;
};

namespace Frustum
{
    bool boxInFrustum;
}

#endif // VIEWING_FRUSTUM_H_INCLUDED
