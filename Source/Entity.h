#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

#include "OpenGL/Glm/glm_transformations.h"

struct Entity
{
    Vector3 position,
            rotation,
            scale       = { 1, 1, 1 };
};

#endif // ENTITY_H_INCLUDED
