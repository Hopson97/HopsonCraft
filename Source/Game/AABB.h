#ifndef AABB_H
#define AABB_H

#include "OpenGL/Glm/glm_transformations.h"

class AABB
{
    public:
        AABB                ( const Vector3& size );

        void setPosition    ( const Vector3& position );

        bool testDown       ( const AABB& other );

    private:
        Vector3 m_position;
        Vector3 m_size;

        Vector3 ftl,    //f = far
                ftr,    //n = near
                ntl,    //b = bottom
                ntr,    //t = top
                fbl,    //l = left
                fbr,    //r = right
                nbl,
                nbr;
};

#endif // AABB_H
