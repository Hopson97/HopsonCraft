#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include "GLM.h"

struct Entity;
class Camera;

namespace Maths
{
    Matrix4 createViewMatrix    (const Camera& camera) noexcept;
    Matrix4 createModelMatrix   (const Entity& entity) noexcept;
    Matrix4 createProjMatrix    (float fieldOfView)    noexcept;

}

#endif // MATRIX_H_INCLUDED
