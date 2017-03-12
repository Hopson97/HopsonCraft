#ifndef FRUSTUM_H_INCLUDED
#define FRUSTUM_H_INCLUDED

#include "../Glm_Common.h"

class Frustum
{
    public:
        Frustum(){};

        void update(const Matrix4& viewMatrix, const Matrix4& projMatrix);

        Vector4 frustum_planes[6];

        bool inFrustum(const Vector4& min, const Vector4& max);
};


#endif // FRUSTUM_H_INCLUDED
