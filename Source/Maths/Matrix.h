#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include "GLM.h"

struct Entity;
class Camera;


Matrix4 createRoationMatrix    (const Entity& entity);

Matrix4 createViewMatrix    (const Camera& camera);
Matrix4 createModelMatrix   (const Entity& entity);
Matrix4 createProjMatrix    (float fieldOfView);



#endif // MATRIX_H_INCLUDED
