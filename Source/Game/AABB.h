#ifndef AABB_H
#define AABB_H

#include "OpenGL/Glm/glm_transformations.h"

class AABB
{
    public:
        AABB                ( const Vector3& size );

        void setPosition    ( const Vector3& position );

    private:
        Vector3 m_position;
        Vector3 m_size;
};

#endif // AABB_H
