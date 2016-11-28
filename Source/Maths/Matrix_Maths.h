#ifndef MATRIX_MATH_H_INCLUDED
#define MATRIX_MATH_H_INCLUDED

#include "../OpenGL/GL_Maths.h"

class Camera;
class Entity;

namespace Maths
{
    Matrix4 createViewMatrix    (const Camera& camera);
    Matrix4 createModelMatrix   (const Entity& entity);

    Matrix4 createPerspectiveMatrix ();
}

#endif // MATRIX_MATH_H_INCLUDED
