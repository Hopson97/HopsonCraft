#ifndef MATHS_H
#define MATHS_H

#include "OpenGL/Glm/glm_transformations.h"

class Camera;

namespace Maths
{
    Matrix4 createViewMatrix ( const Camera& camera );

    Matrix4 createTransforrmationMatrix( const Vector3& translation,
                                         const Vector3& rotation,
                                         const Vector3& scale );
}

#endif // MATHS_H
