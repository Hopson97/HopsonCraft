#ifndef MATHS_H
#define MATHS_H

#include "OpenGL/Glm/glm_transformations.h"
#include "Vector.h"

class Camera;

namespace Maths
{
    Matrix4 createViewMatrix ( const Camera& camera );

    Matrix4 createTransforrmationMatrix( const Vector3& translation,
                                         const Vector3& rotation,
                                         const Vector3& scale );

    Matrix4 createPerspectiveMatrix     ();

    Vector2i worldToChunkLocation   ( const Vector3& worldPos );
    Vector3  worldToBlockInChunkPos ( const Vector3& worldPos );
}

#endif // MATHS_H
