#ifndef MATRIX_MATH_H_INCLUDED
#define MATRIX_MATH_H_INCLUDED

#include "../OpenGL/GL_Maths.h"

class Entity;

namespace Maths
{
    /**
    *  @brief  Generates a transformation matrix
    *  @param  Entity  A camera
    *  @return A transformation/ view matrix
    *
    *   Generates a transformation matrix based on the camera's
    *   position and rotation.
    *   The matrix makes all verticies in the world transform
    *   relative to the player's position
    */
    Matrix4 createViewMatrix    (const Entity& camera);

    /**
    *  @brief  Generates a transformation matrix
    *  @param  entity  A Entity
    *  @return A transformation matrix
    *
    *   Generates a transformation matrix based on an
    *   entities orientation.
    *   The matrix makes all the verticies of this Entity relitive
    *   to it's position
    */
    Matrix4 createModelMatrix   (const Entity& entity);

    /**
    *  @brief  Generates a perspective matrix
    *  @return A perspective matrix
    *
    *   This creates a matrix that transforms verticies to make
    *   the world appear 3D
    */
    Matrix4 createPerspectiveMatrix ();
}

#endif // MATRIX_MATH_H_INCLUDED
